#include "pid_conf.h"
#include "PidController.h"
#include "pins.h"

extern volatile float VL_result;

volatile PIDCTROL PID={
  10,
  0,
  0,
  0,
  0,
  0
};
PidController MOTOR;


void pid_loop()
{
  MOTOR.update_pid(PID.kp,PID.ki,PID.kd);
  MOTOR.update_target(PID.Setpoint);
  MOTOR.out_limit(20,255);
  PID.Output=MOTOR.update(VL_result);
  DELAY_MS(50);
}

