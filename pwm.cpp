#include "pins.h"
#include "pid_conf.h"
#include "pwm.h"

extern volatile PIDCTROL PID;

void init_pwm()
{
  ledcSetup(MOTOR_CHANNEL,FREQ,RESOLUTION_BITS);
  ledcAttachPin(MOTOR_PWM,MOTOR_CHANNEL);
}
void pwm_loop()
{
  Serial.println("pwm");

  ledcWrite(MOTOR_CHANNEL,PID.Output);

}