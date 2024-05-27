#include "pins.h"
#include <Wire.h>
#include 
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;
unsigned long lastDebounceTime4 = 0;
unsigned long debounceDelay = 500; //消抖时间
void setup()
{
  Serial.begin(115200);
  Wire.begin(SDA_PIN,SCL_PIN);
}
