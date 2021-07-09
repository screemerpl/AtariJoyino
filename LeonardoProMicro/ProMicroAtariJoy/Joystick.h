/*
  Joystick.h
  Copyright (c) 2021, Artur Jakubowicz
  
  Simple implementation of joystick HID
  2 buttons and 2 axes
*/

#ifndef JOYSTICK_h
#define JOYSTICK_h

#include "HID.h"

#if !defined(USBCON)
#error This code can only work with arduino Pro mini, Leonardo or UNO/Mega flashed with HoodLoader2
#endif


class Joystick_
{
private:
	int8_t	 xAxis;
	int8_t	 yAxis;
	uint8_t buttons;


public:
	Joystick_();

	void begin();
	void end();

	void setXAxis(int8_t value);
	void setYAxis(int8_t value);

	void setButton(uint8_t button, uint8_t value);
	void pressButton(uint8_t button);
	void releaseButton(uint8_t button);

	void sendState();
};
extern Joystick_ Joystick;

#endif
