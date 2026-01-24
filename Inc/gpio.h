#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>

void gpio_init(void);
bool gpio_button_is_pressed(void);

#endif
