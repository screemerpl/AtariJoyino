# AtariJoyno for ProMicro and Lenoardo

This is Atari joystick adapter for Arduino Pro Micro or leonardo. It does not need any special libraries or additional tools.
Just open the sketch and flash it to arduino then connect a 9PIN DSUB male connector as on this picture:

## Wiring information

### Arduino Pro Micro

YOU SHOULD USE 5V/16MHZ version of the Arduino

Here is a wiring for Arduino Pro Micro, you can use similar one on Leonardo

![Wiring Pro Micro](https://user-images.githubusercontent.com/45807753/125109419-3e24f080-e0db-11eb-8aec-80312689d5bd.png)

### Arduino UNO R3 with Atmega16U2

It is also possible to use this on original UNO R2 with Atmega16U2 chip and HoodLoader2 installed. In this case add line

```#define _UNOHOODLOADER2```
 on top of the source and then flash this to USB MCU with HoodLoader2 
 (more information in link on the bottom). Select the board as on the screenshot:
![Hoodloader2-atmeg16](https://user-images.githubusercontent.com/45807753/125109983-f2bf1200-e0db-11eb-8d03-d39d90a5b9b0.png)

 
 Then the wiring as follows:



As the code works on USB MCU you can remove Atmega328P from the socket :)

More information on HoodLoader2:

Hoodloader 2
[Hoodloader github repo](https://github.com/NicoHood/HoodLoader2)
Check Wiki section for Hardware and Software installatio instruction

