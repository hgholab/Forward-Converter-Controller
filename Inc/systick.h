#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

void systick_init(void);
void systick_delay_ms(uint32_t delay);

#endif
