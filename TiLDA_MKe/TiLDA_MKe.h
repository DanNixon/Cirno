#ifndef _TILDA_MKE_H
#define _TILDA_MKE_H

#include "inttypes.h"

#include "U8glib.h"
#include "UniversalButtons.h"

#define PMIC_BATTERY_FULL 652               // 100%
#define PMIC_BATTERY_GOOD 512               // 25%
#define PMIC_BATTERY_LOW 496                // 17%
#define PMIC_BATTERY_VERYLOW 481            // 9%
#define PMIC_BATTERY_FLAT 465               // 0%

#define PMIC_BATTERY_PERCENT_RATIO 0.534

class TiLDA_MKe
{
  public:
    TiLDA_MKe();

    void setLED(uint8_t led, uint8_t r, uint8_t g, uint8_t b);
    void setLEDs(uint8_t r, uint8_t g, uint8_t b);

    void setBacklight(uint8_t state);
    uint8_t backlight();
    uint8_t toggleBacklight();

    uint8_t getBatteryPercentage();
    float getBatteryVoltage();
    bool isCharging();

    void printWrappedString(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,
        char *text, char delimitOn=' ');

    UniversalButtons buttons;
    U8GLIB_NHD_C12864 glcd;
};

#endif //_TILDA_MKE_H
