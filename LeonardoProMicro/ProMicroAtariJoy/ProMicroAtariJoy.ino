/*
  ProMicroAtariJoy - Atari Joystic adapter for Arduino Pro Mini / Leonardo
  Copyright (c) 2021, Artur Jakubowicz

  Simple Arduino USB adapter to connect Atari style joystick (with 2 button support for Amiga) to any
  USB compatible device. 

*/

/* Include Joystick HID routines from separate class */
#include "Joystick.h"

/* Value to set analog axes to (-range, range) */
#define JOY_MAXVAL 126
/* support for 6 params - 2 butttons and 4 directions */
#define JOY_PARAMS 6

#ifndef _UNOHOODLOADER

#define UP_PIN     2
#define DOWN_PIN   3
#define LEFT_PIN   4
#define RIGHT_PIN  5
#define B1_PIN     6
#define B2_PIN     7

#else
#define UP_PIN     1
#define DOWN_PIN   2
#define LEFT_PIN   3
#define RIGHT_PIN  4
#define B1_PIN     5
#define B2_PIN     6
#endif
uint8_t  pins[JOY_PARAMS]={B1_PIN, B2_PIN, UP_PIN, DOWN_PIN, LEFT_PIN, RIGHT_PIN};

/* Positions of data in buffer */
#define JOY_FIRE1 0
#define JOY_FIRE2 1
#define JOY_UP 2
#define JOY_DOWN 3
#define JOY_LEFT 4
#define JOY_RIGHT 5

unsigned char joystate[JOY_PARAMS]={0,0,0,0,0,0};
unsigned char prevstate[JOY_PARAMS]={0,0,0,0,0,0};

unsigned char inputprevstate[JOY_PARAMS]={0,0,0,0,0,0};

unsigned long lastDebounceTime[JOY_PARAMS] = {0,0,0,0,0,0};  
unsigned long debounceDelay = 10; // 10 msec for quick input response   

void setup() {
     Joystick.begin();
     for (int i=0;i<JOY_PARAMS;i++)
     {
       pinMode(pins[i],INPUT_PULLUP);
     }
}

void loop() {
   for (int i=0;i<JOY_PARAMS;i++)
   {
     processInput(i,pins[i]);
   }
   sendReport();
}

void processInput(uint8_t button, uint8_t pin)
{
  uint8_t reading =  !digitalRead(pin);
  if (reading != inputprevstate[button])
  {
    lastDebounceTime[button] = millis();
    inputprevstate[button] = reading;
  }
  
  if ((millis() - lastDebounceTime[button]) > debounceDelay) {
    if (reading != joystate[button])
    {
       joystate[button] = reading;
    } 
  }
}


void sendReport()
{
      if (isJoystateUpdated())
      {
        updateJoystick();
        // copy data from state to last state
        memcpy(prevstate, joystate, JOY_PARAMS);
      }
}

void updateJoystick()
{
       Joystick.setButton(0,joystate[JOY_FIRE1]==1);
       Joystick.setButton(1,joystate[JOY_FIRE2]==1);

       Joystick.setYAxis(0);
       Joystick.setXAxis(0);

       if (joystate[JOY_UP]==1) Joystick.setYAxis(-JOY_MAXVAL);
       if (joystate[JOY_DOWN]==1)  Joystick.setYAxis(JOY_MAXVAL);
       if (joystate[JOY_LEFT]==1)Joystick.setXAxis(-JOY_MAXVAL);
       if (joystate[JOY_RIGHT]==1) Joystick.setXAxis(JOY_MAXVAL);
     
       Joystick.sendState();
}

bool isJoystateUpdated()
{
  return memcmp(joystate,prevstate,JOY_PARAMS)!=0;
 
}
