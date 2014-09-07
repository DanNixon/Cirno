#ifndef _TILDA_MKE_H
#define _TILDA_MKE_H

#include "inttypes.h"

#include "pins_mke.h"

#include "U8glib.h"
#include "UniversalButtons.h"

class TiLDA_MKe
{
  public:
    TiLDA_MKe();

    void setLED(uint8_t led, uint8_t r, uint8_t g, uint8_t b);

    void setBacklight(uint8_t state);
    uint8_t backlight();

    UniversalButtons buttons;
    U8GLIB_NHD_C12864 glcd;
};

#endif //_TILDA_MKE_H
