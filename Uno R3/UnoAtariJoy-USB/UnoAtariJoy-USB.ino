/*
  UnoAtariJoy - USB controller chip code 
  Copyright (c) 2021, Artur Jakubowicz

  Simple Arduino UNO adapter to connect Atari style joystick (with 2 button support for Amiga) to any
  USB compatible device. 

  NOTE: This sketch needs HookLoader2 instaled into AtMega16u2 inside Arduino UNO. 
  This also means that you need official Arduino UNO R3 or a clone that uses AtMega16u2 as USB controller.
  As cheap clones use cheap USB/serial adapters there is no place to upload this code on them.
*/

/* Use Packet Serial library */ 
#include <PacketSerial.h>
/* Include Joystick HID routines from separate class */
#include "Joystick.h"

/* Positions of data in buffer */
#define JOY_FIRE1 0
#define JOY_FIRE2 1
#define JOY_UP 2
#define JOY_DOWN 3
#define JOY_LEFT 4
#define JOY_RIGHT 5

/* Value to set analog axes to (-range, range) */
#define JOY_MAXVAL 126
/* support for 6 params - 2 butttons and 4 directions */
#define JOY_PARAMS 6

#define PS_BUFFER_SIZE 15

unsigned char joystate[JOY_PARAMS]={0,0,0,0,0,0};
unsigned char prevstate[JOY_PARAMS]={0,0,0,0,0,0};

/* Packet serial - COBS algorithm - max 15 bytes for buffer */
PacketSerial_<COBS, 0, PS_BUFFER_SIZE> packetSerial;

void setup() {
     Serial1.begin(2000000);;
     Joystick.begin();
     packetSerial.setStream(&Serial1);
     packetSerial.setPacketHandler(&onPacketReceived);
}

void loop() {
    packetSerial.update();
}

void onPacketReceived(const uint8_t* buffer, size_t size)
{
  const char sizeOfStatePacket = 8;
  if (size==0) return; // if empty packet received return
  switch (buffer[0]) // use first buffer byte as command
  {
    // for future usage - we may have different packet types
    // currently only 0x01 supported
    case 01: // joystick update
      if (size!=sizeOfStatePacket) break; // invalid packet received
      // copy data from buffer to state
      memcpy(joystate, buffer+1, JOY_PARAMS);
      if (isJoystateUpdated())
      {
        updateJoystick();
        // copy data from state to last state
        memcpy(prevstate, joystate, JOY_PARAMS);
      }
      break;
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
