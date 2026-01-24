#ifndef TIMER_H
#define TIMER_H

/*
 * TIM2 is responsible to generate the PWM signal that drives two switches, namely AH and BL. The
 * frequency of this PWM signal is equal to the switching frequency of the converter, which is 200
 * kHz. Also, TIM2 is used to trigger the ADC SOC (start of conversion) at each switching period,
 * when 15% of the switching period has elapsed. This number (15%) is not chosen arbitrarily and the
 * reason behind choosing this number is that ADC sampling should be away from the PWM edges to have
 * a better quality. Since in our converter the duty cycle at steady-state operation is around 30%,
 * the choice of 15% seems reasonable. The control calculation starts right after ADC EOC (end of
 * conversion), which triggers the ADC ISR, in which we calculate the next switching period duty
 * cycle.
 *
 * TIM3 frequency determines the time for debounce of the push-button. Here the frequency is
 * chosen to be 50 Hz so that a valid press button signal should last for at least 20 ms.
 */

// TIM2 clock frequency (used to generate gates' PWM signal).
#define TIM2_CLK       100000000UL
// TIM2 is used to generate a 200 kHz PWM to drive switches AH and BL.
#define TIM2_FREQUENCY 200000UL
// TIM2 auto-reload register value (This value is 499 which means the duty cycle resolution is 0.2%)
#define TIM2_ARR       (TIM2_CLK / TIM2_FREQUENCY) - 1UL

void tim2_init(void);
void tim3_init(void);

#endif