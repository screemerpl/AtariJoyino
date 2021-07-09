# AtariJoyino

This is the smallest possible Atari Joystick interface to USB using Arduino (Uno R3 or Pro Micro).
It uses standard HID interface for USB available in Leonardo and Pro Micro or HoodLoader2 on UNO

The project contains two versions.

## Arduino with USB support

First version in folder ProMicroAtariJoy is prepared for Arduino with USB support like Pro Micro or Leonardo.
This version CAN be eventually installed on UNO R3 (but not most clones) using additional header inputs for USB MCU. 
In case using normal input headers look on second version.


## Arduino UNO workaround version

Second version in Uno R3 folder contains two projects. One for USB controller, and second for "normal" controller. How this works ? Arduino UNO R3 has really two CPUs. (but not cheap clones). One CPU is programmed in factory to act as USB->Serial converter to interface main CPU. HookLoader2 project is a special firmware that can be flashed to the USB CPU to make it  usable from Arduino IDE. In general this converts UNO R3 into ... two arduinos on one PCB that can communicate with each other using super fast (like 2mbit) serial line. Using this solution it is possible to upload sketch that controls USB port into one CPU and the sketch to read joystick pins into the other making Arduino kind of "multicore" system.

