#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdbool.h>

#define CONTROLLER_REF_TARGET 1.4879f
#define CONTROLLER_REF_STEPS  200

extern bool controller_ref_reached_target;
extern float controller_reference;

float controller_step(float x);
void controller_step_ref(float target, float step);
void controller_reset(void);

#endif