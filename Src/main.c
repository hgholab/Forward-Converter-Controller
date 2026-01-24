#include "adc.h"
#include "clock.h"
#include "fpu.h"
#include "gpio.h"
#include "iwdg.h"
#include "pwm.h"
#include "systick.h"
#include "timer.h"

int main(void)
{
        fpu_enable();
        clock_init();
        systick_init();
        gpio_init();
        tim2_init();
        tim3_init();
        pwm_tim2_ch1_init();
        adc_init();
        iwdg_init();

        for (;;)
                iwdg_pet_the_dog();
}