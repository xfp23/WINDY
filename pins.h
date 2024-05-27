#ifndef PINS_H
#define PINS_H
#include <Arduino.h>

#define SDA_PIN 3
#define SCL_PIN 2

#define MOTOR_PWM 9
#define BUTTON_PID_SET 1
#define BUTTON_MODE 8
#define BUTTON_KP 5
#define BUTTON_KI 6

#define DELAY_MS(S) vTaskDelay(S / portTICK_PERIOD_MS)//毫秒级延时
#define DELAY_US(S) vTaskDelay((S / 1000) / portTICK_PERIOD_MS) // 延时（微秒级）
 

#endif