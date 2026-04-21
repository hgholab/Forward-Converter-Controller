#include <stdio.h>

#include "stm32f4xx.h"

#include "systick.h"

#include "adc.h"
#include "clock.h"
#include "controller.h"
#include "gpio.h"

// SysTick frequency in Hz
#define SYSTICK_FREQUENCY 1000UL

// systick_ticks is incremented SYSTICK_FREQUENCY times every second in SysTick_Handler ISR.
static volatile uint32_t systick_ticks = 0UL;

void SysTick_Handler(void)
{
        systick_ticks++;

        if (systick_ticks % 400UL == 0)
        {
                for (int i = 0; i < 63; i++)
                {
                        printf("\b \b");
                }

                printf("       %05.2f%%              %4.2fV                  %05.2fV      ",
                       control_signal * 100.0f,
                       adc_value,
                       adc_value * 5.0f / CONTROLLER_REF_TARGET);

                // printf(" %05.2f%%, %4.2fV, %05.2fV",
                //        control_signal * 100.0f,
                //        adc_value,
                //        adc_value * 5.0f / CONTROLLER_REF_TARGET);
        }
}

void systick_init(void)
{
        // Disable SysTick timer before configuration.
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

        // Enable SysTick interrupt.
        SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

        // Set SysTick clock source to cpu clock (HCLK).
        SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;

        // Set reload value.
        SysTick->LOAD = HCLK / SYSTICK_FREQUENCY - 1;

        /*
         * Clear current value so it starts counting from LOAD immediately (SysTick is a 24-bit
         * down-counter).
         */
        SysTick->VAL = 0U;

        // Enable SysTick timer.
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void systick_delay_ms(uint32_t delay)
{
        uint32_t now = systick_ticks;
        while (systick_ticks - now <= delay)
                ;
}