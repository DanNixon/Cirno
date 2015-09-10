#ifndef _TILDA_MKE_H
#define _TILDA_MKE_H

#include <inttypes.h>

#include <U8glib.h>
#include <UniversalInputManager.h>

#define PMIC_BATTERY_FULL     652  // 100%
#define PMIC_BATTERY_GOOD     512  // 25%
#define PMIC_BATTERY_LOW      496  // 17%
#define PMIC_BATTERY_VERYLOW  481  // 9%
#define PMIC_BATTERY_FLAT     465  // 0%

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

    void drawWrappedStr(uint8_t x, uint8_t y, uint8_t w, uint8_t h,
        char *text, char delimiter=' ');

    UniversalInputManager buttons;
    U8GLIB_NHD_C12864 glcd;

  private:
    bool subStringOverLength(char *string, uint8_t len, uint8_t limit);
    char *getNewlinePtr(char *string, uint8_t width, char delimiter);

};

#endif //_TILDA_MKE_H
