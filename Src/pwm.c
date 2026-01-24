#include "stm32f4xx.h"

#include "pwm.h"

#define TIM_CCMR1_OC1M_PWM1 (6UL << TIM_CCMR1_OC1M_Pos)

void pwm_tim2_ch1_init(void)
{
        // Disable CH1 output first.
        pwm_tim2_ch1_disable();

        /*
         * Clear OC1M (mode bits) and OC1PE (preload enable) first. Then we set the
         * channel one on PWM mode 1 and also before enabling the channel output, we
         * enable the preload.
         */
        TIM2->CCMR1 &= ~(TIM_CCMR1_OC1M_Msk | TIM_CCMR1_OC1PE);
        // PWM mode 1 on CH1.
        TIM2->CCMR1 |= TIM_CCMR1_OC1M_PWM1;

        // Clear CC1P to make the output active high.
        TIM2->CCER &= ~TIM_CCER_CC1P;

        // Enable CCR1 preload because we disabled it earlier.
        TIM2->CCMR1 |= TIM_CCMR1_OC1PE;
}

void pwm_tim2_ch1_disable(void)
{
        /*
         * From the reference manual:
         *      CC1E: Capture/Compare 1 output enable.
         *      CC1 channel configured as output:
         *              0: Off - OC1 is not active
         *              1: On  - OC1 signal is output on the corresponding output pin
         */
        TIM2->CCER &= ~TIM_CCER_CC1E;
}

void pwm_tim2_ch1_enable(void)
{
        TIM2->CCER |= TIM_CCER_CC1E;
}