#include <Arduino.h>
#include "pins.h"
#include "pid_conf.h"
extern volatile PIDCTROL PID;

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;
unsigned long lastDebounceTime4 = 0;
unsigned long debounceDelay = 500; 
void set_point()
{
  unsigned long currentMillis = millis();
  if (currentMillis - lastDebounceTime1 >= debounceDelay)
  {
    lastDebounceTime1 = currentMillis;
     if(PID.Setpoint<50)
  {
    PID.Setpoint+=10;
  } else {
    PID.Setpoint=10;
  }
  }
 
}

void set_mode()
{
  static short sta=0;
 unsigned long currentMillis = millis();
 if (currentMillis - lastDebounceTime2 >= debounceDelay)
 {
  lastDebounceTime2 = currentMillis;
   if(sta<3)
  {
    sta++;
  } else {
    sta=0;
  }
  switch(sta)
  {
  case 0 : 
  PID.Setpoint+=2;
  break;
  case 1:
  PID.Setpoint+=4;
  break;
  case 2:
  PID.Setpoint+=8;
  break;
  default :
  sta=0;
  break;

  }

 }
 
}

void set_kp()
{
  unsigned long currentMillis = millis();
   if (currentMillis - lastDebounceTime3 >= debounceDelay)
   {
    lastDebounceTime3 = currentMillis;
      PID.kp+=10;
   }

}

void set_ki()
{
    unsigned long currentMillis = millis();
   if (currentMillis - lastDebounceTime3 >= debounceDelay)
   {
    lastDebounceTime4 = currentMillis;
      PID.ki+=1;
   }

}
void init_button()
{
  pinMode(BUTTON_PID_SET,INPUT_PULLUP);
  pinMode(BUTTON_MODE,INPUT_PULLUP);
  pinMode(BUTTON_KP,INPUT_PULLUP);
  pinMode(BUTTON_KI,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PID_SET), set_point , FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_MODE),set_mode ,FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_KP), set_kp,FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_KI), set_ki,FALLING);
}