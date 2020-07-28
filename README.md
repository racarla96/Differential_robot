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

## TODO:
 - [ ] Periodic cyclic task -> [HOWTO build a basic cyclic application](https://wiki.linuxfoundation.org/realtime/documentation/howto/applications/cyclic)
 - [ ] Machine state to read quadrature encoder X4
