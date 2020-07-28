#include <iostream>

#include <pigpio.h>

#include "rotary_encoder.hpp"

#include <unistd.h>

/*

REQUIRES

A rotary encoder contacts A and B connected to separate gpios and
the common contact connected to Pi ground.

TO BUILD

g++ -o rot_enc_cpp test_rotary_encoder.cpp rotary_encoder.cpp -lpigpio -lrt

TO RUN

sudo ./rot_enc_cpp

USEFUL LINKS

https://stackoverflow.com/questions/31978324/what-exactly-is-stdatomic
http://makeatronics.blogspot.com/2013/02/efficiently-reading-quadrature-with.html

*/

using namespace std;

int main(int argc, char *argv[])
{
   if (gpioInitialise() < 0) return 1;

   re_decoder dec(7, 8);

   for(int i = 0; i < 100; i++) {
      cout << dec.re_get_counts() << endl;
      sleep(1);
   }

   dec.re_cancel();

   gpioTerminate();
}

