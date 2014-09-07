#ifndef _TILDA_DISPLAY_H
#define _TILDA_DISPLAY_H

#include "inttypes.h"
#include "U8glib.h"

class Display
{
  public:
    Display();

    void setBacklight(uint8_t);
    uint8_t backlight();

    U8GLIB_NHD_C12864 glcd;
};

#endif //_TILDA_DISPLAY_H
