#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>

typedef enum
{
        GPIO_PORT_A,
        GPIO_PORT_B,
        GPIO_PORT_C,
        GPIO_PORT_D,
        GPIO_PORT_E,
        GPIO_PORT_H
} gpio_port_t;

typedef enum
{
        GPIO_PIN_0,
        GPIO_PIN_1,
        GPIO_PIN_2,
        GPIO_PIN_3,
        GPIO_PIN_4,
        GPIO_PIN_5,
        GPIO_PIN_6,
        GPIO_PIN_7,
        GPIO_PIN_8,
        GPIO_PIN_9,
        GPIO_PIN_10,
        GPIO_PIN_11,
        GPIO_PIN_12,
        GPIO_PIN_13,
        GPIO_PIN_14,
        GPIO_PIN_15
} gpio_pin_t;

void gpio_init(void);
bool gpio_button_is_pressed(void);
void gpio_clear_pin(gpio_port_t port, gpio_pin_t pin);
void gpio_set_pin(gpio_port_t port, gpio_pin_t pin);

#endif
