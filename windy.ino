#include "pins.h"
#include <Wire.h>
#include "pwm.h"
#include "pid_conf.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
extern void pwm_loop();
extern void screen_loop();
extern  void vl53_loop();
extern void init_screen();
extern void init_button();
extern void pid_loop();
//extern void VL53_Application(void *param);
//extern void screen_Application(void *param);
extern void init_vl53();

extern volatile PIDCTROL PID;

hw_timer_t *timerA=NULL;

void  IRAM_ATTR timerAcallback()
{
  ledcWrite(MOTOR_CHANNEL,153);
}
void setup() { 
    Wire.begin(SDA_PIN, SCL_PIN);
    Serial.begin(115200);
    init_vl53();
    init_screen();
    init_pwm();
    timerA=timerBegin(0,80,true);
    timerAttachInterrupt(timerA,&timerAcallback,true);
    timerAlarmWrite(timerA,2000,true);
     timerAlarmEnable(timerA);
    init_button();

    //vTaskStartScheduler(); // 启动任务调度器
}

void loop()
{
  vl53_loop();
   pid_loop();
   screen_loop();


 DELAY_MS(100);
}