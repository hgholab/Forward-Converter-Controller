#include <stdio.h>

#include "adc.h"
#include "clock.h"
#include "fpu.h"
#include "gpio.h"
#include "iwdg.h"
#include "pwm.h"
#include "systick.h"
#include "timer.h"
#include "uart.h"

int main(void)
{
        fpu_enable();
        clock_init();
        gpio_init();
        setbuf(stdout, NULL);
        uart2_init();
        tim2_init();
        tim3_init();
        pwm_tim2_ch1_init();
        adc_init();
        systick_init();
        iwdg_init();

        for (;;)
                iwdg_pet_the_dog();
}