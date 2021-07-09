/*
  UnoAtariJoy - Main controller chip code 
  Copyright (c) 2021, Artur Jakubowicz

  Simple Arduino UNO adapter to connect Atari style joystick (with 2 button support for Amiga) to any
  USB compatible device. 

  NOTE: This sketch needs HookLoader2 instaled into AtMega16u2 inside Arduino UNO. 
  This also means that you need official Arduino UNO R3 or a clone that uses AtMega16u2 as USB controller.
  As cheap clones use cheap USB/serial adapters there is no place to upload this code on them.
*/

/* Use Packet Serial library */ 
#include <PacketSerial.h>

#define UP_PIN     3
#define DOWN_PIN   4
#define LEFT_PIN   5
#define RIGHT_PIN  6
#define B1_PIN     7
#define B2_PIN     8

#define JOY_PARAMS 6

uint8_t  pins[JOY_PARAMS]={B1_PIN, B2_PIN, UP_PIN, DOWN_PIN, LEFT_PIN, RIGHT_PIN};

uint8_t  joystate[JOY_PARAMS]={0,0,0,0,0,0};
uint8_t  prevstate[JOY_PARAMS]={0,0,0,0,0,0};

unsigned long lastDebounceTime[JOY_PARAMS] = {0,0,0,0,0,0};  
unsigned long debounceDelay = 10; // 10 msec for quick input response   

#define PS_BUFFER_SIZE 15
/* Packet serial - COBS algorithm - max 15 bytes for buffer */
PacketSerial_<COBS, 0, PS_BUFFER_SIZE> packetSerial;

void setup() {
  Serial.begin(2000000);
  delay(1000); // small delay to make sure USB controller booted and ready
  
  for (int i=0;i<JOY_PARAMS;i++)
  {
     pinMode(pins[i],INPUT_PULLUP);
  }
  packetSerial.setStream(&Serial);
  packetSerial.setPacketHandler(&onPacketReceived);
}

void loop() {
  for (int i=0;i<JOY_PARAMS;i++)
  {
    processInput(i,pins[i]);
  }
  sendBuffer(); 
}


void onPacketReceived(const uint8_t* buffer, size_t size)
{
}

void processInput(uint8_t button, uint8_t pin)
{
  uint8_t reading =  !digitalRead(pin);
  if (reading != prevstate[button])
  {
    lastDebounceTime[button] = millis();
    prevstate[button] = reading;
  }
  
  if ((millis() - lastDebounceTime[button]) > debounceDelay) {
    if (reading != joystate[button])
    {
       joystate[button] = reading;
    } 
  }
}

void sendBuffer()
{
  const char sizeOfStatePacket = 8;
  char sendbuffer[sizeOfStatePacketlocal]={0x01,joystate[0],joystate[1],joystate[2],joystate[3],joystate[4],joystate[5],0x00};
  packetSerial.send(sendbuffer, 8);
}
