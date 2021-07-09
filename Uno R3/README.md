# AtariJoyino for Arduino UNO

This is Atari joystick adapter for Arduino UNO. This is dual CPU version . It uses HoodLoader2 and PacketSerial library
to establish communication between MCU's. Also this does not work on MOST of clones as they do not use AtMega16U2

To flash this install and burn HoodLoader2 as described here:

Hoodloader 2

[Hoodloader github repo](https://github.com/NicoHood/HoodLoader2)

Check Wiki section for Hardware and Software installation instruction

Also you need additional library in your Arduino IDE from here

[PacketSerialrepo](https://github.com/bakercp/PacketSerial)

After installing those two components (and flashing Hoodloader2 into Arduino)

Open Sketch "UnoAtariJoy-USB" and load it onto USB MCU (selecting Board "HoodLoader2 Atmega16U2")

Open Sketch "UnoAtariJoy-IO" and load it onto IO MCU (selecting Board "Hoodloader2 UNO")


## Wiring information

### Arduino UNO R3 with Atmega16U2
![Uno wiring IO](https://user-images.githubusercontent.com/45807753/125113815-0620ac00-e0e1-11eb-9e41-aeb989022d53.png)


 


