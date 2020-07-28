#ifndef ROTARY_ENCODER_HPP
#define ROTARY_ENCODER_HPP

#include <stdint.h>

#include <atomic>

class re_decoder
{
   std::atomic<long> counts {0};

   int mygpioA, mygpioB, levA, levB;

   void _pulse(int gpio, int level, uint32_t tick);

   /* Need a static callback to link with C. */
   static void _pulseEx(int gpio, int level, uint32_t tick, void *user);

   public:
   /*
      This function establishes a rotary encoder on gpioA and gpioB.

      When the encoder is turned the callback function is called.
   */
   re_decoder(int gpioA, int gpioB);

   /* 
      This function returns the counts of encoder
   */
   long re_get_counts();

   /* 
      This function clear the counts of encoder
   */
   void re_clear_counts();

   /*
      This function releases the resources used by the decoder.
   */
   void re_cancel(void);
};

#endif
