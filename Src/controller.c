#include "controller.h"

#define MAX_DUTY 0.45f

/*
 * Static variables storing past samples:
 *   x1 = x[k-1], x2 = x[k-2]
 *   y1 = y[k-1], y2 = y[k-2]
 * Here, x denotes the error signal and y denotes the compensator output signal.
 *
 * These implement the memory required by the discrete-time compensator.
 */
static float x1 = 0.0f, x2 = 0.0f;
static float y1 = 0.0f, y2 = 0.0f;

static float controller_reference = 0.0f; // Controller instantaneous reference value.

float controller_step(float x)
{
        /*
         * Coefficients derived from the z-domain transfer function:
         *
         *            10.290000 - 18.280000 z^-1 + 8.094000 z^-2
         * Gcd(z) = ----------------------------------------------
         *             1.000000 -  0.903900 z^-1 - 0.096090 z^-2
         *
         * Difference equation:
         *
         *   y[k] = 10.290000 * x[k]
         *        - 18.280000 * x[k-1]
         *        +  8.094000 * x[k-2]
         *        +  0.903900 * y[k-1]
         *        +  0.096090 * y[k-2]
         */
        const float b0 = 10.29f;
        const float b1 = -18.28f;
        const float b2 = 8.094f;
        const float c1 = 0.9039f;
        const float c2 = 0.09609f;

        // Compute current output y[k] using the difference equation.
        float y = (b0 * x) + (b1 * x1) + (b2 * x2) + (c1 * y1) + (c2 * y2);

        /*
         * Shift for next instant:
         *   x2 <- x1,  x1 <- x
         *   y2 <- y1,  y1 <- y
         */
        x2 = x1;
        x1 = x;

        y2 = y1;
        y1 = y;

        /**
         * Clamp the compensator output to make sure that duty cycle stays equal or less than
         * MAX_DUTY which we have chosen to be 0.45 so that we have enough headroom. In 2-switch
         * forward converter, duty cycle should be less than 0.5 (50%) so that the transformer could
         * demagnetize safely.
         */
        y = y > MAX_DUTY ? MAX_DUTY : y;

        return y;
}

/*
 * This function generates the reference voltage which increases like a ramp at the beginning to
 * prevent current inrush. Smaller steps make the reference reach its final value slower, but has
 * better effect on inrush current alleviation.
 */
void controller_step_ref(float current, float target, float step)
{
        // At any call of this function, we should have current <= target.
        if (current < target)
        {
                current += step;
                if (current > target)
                {
                        current = target;
                }
        }
        controller_reference = current;
}
/**
 * This function is used to reset the controller variables so that when the converter is turned
 * on again it can start from a clean slate.
 */
void controller_reset(void)
{
        controller_reference = 0.0f;
        x1                   = 0.0f;
        x2                   = 0.0f;
        y1                   = 0.0f;
        y2                   = 0.0f;
}

float controller_get_ref(void)
{
        return controller_reference;
}