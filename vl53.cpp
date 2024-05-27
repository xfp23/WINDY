#include "Adafruit_VL53L0X.h"
#include "oled.h"
#include "pins.h"
#include <Wire.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
volatile float VL_result;

void init_vl53() {
  Serial.begin(115200);
  //Wire.begin(SDA_PIN, SCL_PIN); // 确保I2C引脚正确初始化

  // 增加一些初始化诊断输出
  Serial.println("Initializing VL53L0X...");

  if (!lox.begin(VL53L0X_I2C_ADDR, &Wire)) {
    Serial.println("Failed to initialize VL53L0X sensor!");
    //while (1); // 停止程序运行，指示传感器初始化失败
  }
  Serial.println("VL53L0X sensor initialized successfully.");
}

void vl53_loop() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) { // if not out of range
    VL_result = measure.RangeMilliMeter;
    //Serial.println(VL_result); // 打印测量值
  } else {
    VL_result = -1; // 指示测量值超出范围
  }
}