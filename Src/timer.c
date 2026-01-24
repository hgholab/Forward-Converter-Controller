#include <stdbool.h>

#include "stm32f4xx.h"

#include "timer.h"

#include "clock.h"
#include "controller.h"
#include "gpio.h"
#include "pwm.h"
#include "systick.h"

#define TIM3_CLK       10000UL
#define TIM3_FREQUENCY 50UL
#define TIM3_ARR       (TIM3_CLK / TIM3_FREQUENCY) - 1UL

static bool converter_is_on         = false;
// This variable shows previous state of button being pushed or not (stable state).
static bool button_last_push_status = false;

void TIM3_IRQHandler(void)
{
        // Clear UIF flag.
        TIM3->SR &= ~TIM_SR_UIF;

        bool button_is_pressed = gpio_button_is_pressed();

        // Detect change in button status to register it as one button press.
        if (button_is_pressed && !button_last_push_status)
        {
                if (converter_is_on)
                {
                        // Stop TIM2 counter.
                        TIM2->CR1 &= ~TIM_CR1_CEN;

                        // Disable the PWM signal.
                        pwm_tim2_ch1_disable();

                        // Reset TIM2 counter.
                        TIM2->CNT = 0UL;

                        // Clear TIM2 CH1 CCR (CCR1).
                        TIM2->CCR1 = 0U;

                        // Reset the controller.
                        controller_reset();
                }
                else
                {
                        /*
                         * This delay makes sure that the output voltage and the filter inductor
                         * current is 0. The output filter and the load take only about 50 ms
                         * maxmium to get to zero state.
                         */
                        systick_delay_ms(200UL);

                        // Enable the PWM signal.
                        pwm_tim2_ch1_enable();

                        // Start TIM2 counter.
                        TIM2->CR1 |= TIM_CR1_CEN;
                }
                converter_is_on = !converter_is_on;
        }
        button_last_push_status = button_is_pressed;
}

void tim2_init(void)
{
        // Enable clock for TIM2.
        RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

        /*
         * PCLK1 = HCLK / 2 = 50 MHz (max allowed on STM32F411RE).
         * APB1 timer clock = 100 MHz (because APB1 prescaler = 2).
         * We want for TIM2 to run at frequency of TIM2_CLK = 100 MHz.
         */

        // Calculate the value of prescaler so TIM2 runs at 100 MHz.
        uint32_t prescaler = (APB1_TIM_CLK / TIM2_CLK) - 1UL;

        // Set prescaler and auto-reload.
        TIM2->PSC = prescaler;
        TIM2->ARR = TIM2_ARR;

        // Set up-counting, edge-aligned mode.
        TIM2->CR1 &= ~(TIM_CR1_CMS | TIM_CR1_DIR);

        // Enable ARR preload (prescaler (PSC) is always buffered).
        TIM2->CR1 |= TIM_CR1_ARPE;

        // Enable CCR1 and CCR2 preload.
        TIM2->CCMR1 |= TIM_CCMR1_OC1PE;
        TIM2->CCMR1 |= TIM_CCMR1_OC2PE;

        // Set CCR1 to 0 to make sure that the PWM duty cycle is 0 initially.
        TIM2->CCR1 = 0U;

        /*
         * Calculate the CCR2 value so that it triggers the ADC SOC (start of
         * conversion) when 15% of the switching period has elapsed. This causes a better reading
         * where the voltage is less affected by switching noises.
         */
        TIM2->CCR2 = (uint32_t)((15.0f / 100.0f) * TIM2_ARR);

        // Generate an update first to load preloaded values.
        TIM2->EGR |= TIM_EGR_UG;

        // Set Master Mode Selection so that OC2REF signal is used as trigger output (TRGO).
        TIM2->CR2 |= TIM_CR2_MMS_2 | TIM_CR2_MMS_0;

        // Clear the Output Compare 2 Mode bits.
        TIM2->CCMR1 &= ~TIM_CCMR1_OC2M;
        // Set OC2M to PWM Mode 1 (Binary 110 = 6)
        TIM2->CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1);

        /*
         * We do not enable the TIM2 counter yet, so that it will be enabled when we start the
         * converter and its control loop using the push button. In fact, we disable it here to make
         * sure it does not start counting.
         */
        TIM2->CR1 &= ~TIM_CR1_CEN;
}

void tim3_init(void)
{
        // Enable clock for TIM3.
        RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

        /*
         * PCLK1 = HCLK / 2 = 50 MHz (max allowed on STM32F411).
         * APB1 timer clock = 100 MHz (because APB1 prescaler = 2).
         * We want for timer 3 to run at frequency of TIM3_CLK = 10 kHz.
         */

        // Calculate the value of prescaler so timer 3 runs at 10 kHz.
        uint32_t prescaler = (APB1_TIM_CLK / TIM3_CLK) - 1UL;

        // Set prescaler and auto-reload.
        TIM3->PSC = prescaler;
        TIM3->ARR = TIM3_ARR;

        // Set up-counting, edge-aligned mode.
        TIM3->CR1 &= ~(TIM_CR1_CMS | TIM_CR1_DIR);

        // Enable ARR preload (prescaler (PSC) is always buffered).
        TIM3->CR1 |= TIM_CR1_ARPE;

        // Enable update event interrupt.
        TIM3->DIER |= TIM_DIER_UIE;

        // Generate an update first to load preloaded value.
        TIM3->EGR |= TIM_EGR_UG;

        // Clear pending flags.
        TIM3->SR = 0;

        // Clear pending interrupt.
        NVIC_ClearPendingIRQ(TIM3_IRQn);

        // Set priority and enable TIM3 interrupt in NVIC (TIM3 priority is less than ADC).
        NVIC_SetPriority(TIM3_IRQn, 1);
        NVIC_EnableIRQ(TIM3_IRQn);

        // Enable TIM3 counter.
        TIM3->CR1 |= TIM_CR1_CEN;
}