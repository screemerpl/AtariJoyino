/*
  Joystick.cpp
  Copyright (c) 2021, Artur Jakubowicz

  Simple implementation of joystick HID
  2 buttons and 2 axes
*/

#include "Joystick.h"

/* Report ID */
#define JOYSTICK_REPORT_ID 0x03
/* Report data structure - 3 bytes  
 *  
 *  byte 0 - button state
 *  byte 1 - xaxis value
 *  byte 2 - yaxis value
 */
#define JOYSTICK_STATE_SIZE 3

static const uint8_t _reportDescriptor[] PROGMEM = {
  
	// Joystick
	0x05, 0x01,			      // USAGE_PAGE (Generic Desktop)
	0x09, 0x04,			      // USAGE (Joystick)
	0xa1, 0x01,			      // COLLECTION (Application)
	0x85, JOYSTICK_REPORT_ID, //   REPORT_ID (3)

  // 2 Buttons
  0x05, 0x09,           //   USAGE_PAGE (Button)
  0x19, 0x01,           //   USAGE_MINIMUM (Button 1)
  0x29, 0x02,           //   USAGE_MAXIMUM (Button 2)
  0x15, 0x00,           //   LOGICAL_MINIMUM (0)
  0x25, 0x01,           //   LOGICAL_MAXIMUM (1)
  0x75, 0x01,           //   REPORT_SIZE (1)
  0x95, 0x08,           //   REPORT_COUNT (8) - even 6 not in use we need to have byte align here
  0x55, 0x00,           //   UNIT_EXPONENT (0)
  0x65, 0x00,           //   UNIT (None)
  0x81, 0x02,           //   INPUT (Data,Var,Abs)

	// X, Y  Axis
  0x05, 0x01,           //   USAGE_PAGE (Generic Desktop)
	0x15, 0x00,			      //   LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,	      //   LOGICAL_MAXIMUM (255)
	0x75, 0x08,			      //   REPORT_SIZE (8)
	0x09, 0x01,			      //   USAGE (Pointer)
	0xA1, 0x00,			      //   COLLECTION (Physical)
	0x09, 0x30,		          //     USAGE (x)
	0x09, 0x31,		          //     USAGE (y)
	0x95, 0x02,		          //     REPORT_COUNT (2)
	0x81, 0x02,		          //     INPUT (Data,Var,Abs)
	0xc0,				      //   END_COLLECTION                           
	0xc0				      // END_COLLECTION
};

Joystick_::Joystick_()
{
	static HIDSubDescriptor node(_reportDescriptor, sizeof(_reportDescriptor));
	HID().AppendDescriptor(&node);
  
	xAxis = 0;
	yAxis = 0;
	buttons = 0;
}

void Joystick_::begin()
{
	sendState();
}

void Joystick_::end()
{
}

void Joystick_::setButton(uint8_t button, uint8_t value)
{
	if (value == 0)
		  bitClear(buttons, button);
	else
		  bitSet(buttons, button);
}


void Joystick_::setXAxis(int8_t value)
{
	xAxis = value;

}
void Joystick_::setYAxis(int8_t value)
{
	yAxis = value;

}

void Joystick_::sendState()
{
	uint8_t data[JOYSTICK_STATE_SIZE];
	data[0] = buttons;	
	data[1] = xAxis + 127;
	data[2] = yAxis + 127;
	HID().SendReport(JOYSTICK_REPORT_ID, data, JOYSTICK_STATE_SIZE);
}

Joystick_ Joystick;
