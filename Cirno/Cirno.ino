#include "U8glib.h"

#include "pins_mke.h"

#include "Display.h"
#include "Leds.h"

Display display;
Leds leds;

void setup(void)
{
  display.setBacklight(LCD_BACKLIGHT_ON);

  display.glcd.setFont(u8g_font_6x10);
  display.glcd.setFontRefHeightExtendedText();
  display.glcd.setDefaultForegroundColor();
  display.glcd.setFontPosTop();

  leds.setLED(1, 0, 1, 0);
  leds.setLED(2, 1, 0, 0);
}

void loop()
{
  display.glcd.firstPage();
  do
  {
    display.glcd.drawStr(10, 20, "Hello, World!");
  }
  while(display.glcd.nextPage());

  delay(100);
}
