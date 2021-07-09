# AtariJoyno for ProMicro and Lenoardo

This is Atari joystick adapter for Arduino Pro Micro or leonardo. It does not need any special libraries or additional tools.
Just open the sketch and flash it to arduino then connect a 9PIN DSUB male connector as on this picture:

## Wiring information

### Arduino Pro Micro

Here is a wiring for Arduino Pro Micro, you can use similar one on Leonardo



### Arduino Pro Micro

It is also possible to use this on original UNO R2 with Atmega16U2 chip and HoodLoader2 installed. In this case add line

```#define _UNOHOODLOADER2```
 on top of the source and then flash this to USB MCU. Then the wiring as follows:


As the code works on USB MCU you can remove Atmega328P from the socket :)

More information on HoodLoader2:

Hoodloader 2
[Hoodloader github repo](https://github.com/NicoHood/HoodLoader2)
Check Wiki section for Hardware and Software installatio instruction

