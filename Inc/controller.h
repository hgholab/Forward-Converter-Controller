#ifndef CONTROLLER_H
#define CONTROLLER_H

#define CONTROLLER_REF_TARGET 1.5f
#define CONTROLLER_REF_STEPS  1000

float controller_step(float x);
void controller_step_ref(float current, float target, float step);
void controller_reset(void);
float controller_get_ref(void);

#endif