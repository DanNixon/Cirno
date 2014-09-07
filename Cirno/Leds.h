#ifndef _TILDA_LEDS_H
#define _TILDA_LEDS_H

#include "inttypes.h"

class Leds
{
  public:
    Leds();

    void setLED(uint8_t led, uint8_t r, uint8_t g, uint8_t b);
};

#endif //_TILDA_LEDS_H
