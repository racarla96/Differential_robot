# Differential_robot

## Steps:

1. Install Raspberry Pi OS (32-bit) Lite. \
For the official Raspberry Pi OS, if you need to manually log in, the default user name is pi, with password raspberry. \
Remember to create a empty file with the name 'ssh' in the boot partition

2. Install Preempt-RT Patch for any Raspberry Pi.  
[Tutorial - Raspberry Pi 4B: Real-Time System using Preempt-RT (kernel 4.19.y)](https://lemariva.com/blog/2019/09/raspberry-pi-4b-preempt-rt-kernel-419y-performance-test)

3. Install pigpio library \
[Pigpio Library](http://abyz.me.uk/rpi/pigpio/index.html) \
[HOWTO install library](http://abyz.me.uk/rpi/pigpio/download.html)

4. Encoder and Motor Library

5. Periodic control task for position and velocity control of the wheel \
[PID Digital controller implementation example](https://www.picuino.com/es/arduprog/control-pid-digital.html) \
Design position and velocity controller

6. Reorganize the code and structure of the project

## DOIT:
 - [x] Machine state to read quadrature encoder X4 
 - [x] Motor Driver DRV8838
 - [x] Periodic cyclic task -> [HOWTO build a basic cyclic application](https://wiki.linuxfoundation.org/realtime/documentation/howto/applications/cyclic)
 - [x] Transfer function of first order (angular velocity) with Matlab with system identification toolbox 
 - [x] Step 5: Design position and velocity controller.
 
## TODO:
 - [ ] Use PID controller for velocity control with ROS.

 
## LINKS:
- [Estimate velocity 1](https://www.embeddedrelated.com/showarticle/158.php)
- [Estimate velocity 2](https://www.motioncontroltips.com/how-are-encoders-used-for-speed-measurement/)
 
## WHY USE ...?
- [Cpp Inline functions](https://www.geeksforgeeks.org/inline-functions-cpp/)

## TOOLS used:
- [Draw.io](https://app.diagrams.net/) for creating diagram like electrical schematic.
- MATLAB



