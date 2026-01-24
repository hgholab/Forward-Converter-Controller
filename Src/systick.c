#include "stm32f4xx.h"

#include "systick.h"

#include "clock.h"

// SysTick frequency in Hz
#define SYSTICK_FREQUENCY 1000UL

// systick_ticks is incremented SYSTICK_FREQUENCY times every second in SysTick_Handler ISR.
static volatile uint32_t systick_ticks = 0UL;

void SysTick_Handler(void)
{
        systick_ticks++;
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