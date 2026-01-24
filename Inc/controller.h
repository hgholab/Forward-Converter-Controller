#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdbool.h>

#define CONTROLLER_REF_TARGET 1.5f
#define CONTROLLER_REF_STEPS  1000

extern bool controller_ref_reached_target;

float controller_step(float x);
void controller_reset(void);
float controller_get_ref(void);

#endif