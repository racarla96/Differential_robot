#include <iostream>

#include <pigpio.h>

#include "drv8838.hpp"

#include <unistd.h>

/*

REQUIRES

???

TO BUILD

g++ -o test_motor_cpp test_motor.cpp drv8838.cpp -lpigpio -lrt

TO RUN

sudo ./test_motor_cpp

USEFUL LINKS
*/

using namespace std;

int main(int argc, char *argv[])
{
   if (gpioInitialise() < 0) return 1;

   drv8838 drv(16, 20);

   cout << "FORWARD" << endl;

   drv.setDirection(FORWARD);

   for(int i = 0; i < 250; i = i + 50) {
      drv.setSpeed(i);
      cout << "PWM " << i << endl;
      sleep(2);
   }

   drv.setSpeed(0);
   sleep(2);

   cout << "BACKWARD" << endl;

   drv.setDirection(BACKWARD);

   for(int i = 0; i < 250; i = i + 50) {
      drv.setSpeed(i);
      cout << "PWM " << i << endl;
      sleep(2);
   }

   drv.setSpeed(0);
   sleep(2);

   gpioTerminate();
}

