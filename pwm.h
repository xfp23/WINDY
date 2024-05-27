#ifndef PWM_H
#define PWM_H

#define FREQ 5000
#define RESOLUTION_BITS 8
#define MOTOR_CHANNEL 0

void init_pwm();
void pwm_loop();

#endif