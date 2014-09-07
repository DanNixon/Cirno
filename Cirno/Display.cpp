#include "Display.h"

#include "Arduino.h"
#include "pins_mke.h"

/* TODO */
/* LCD_POWER should really have software PWM, since it is used for contrast control */
/* It needs to be added for the LEDs anyway */

Display::Display() :
  glcd(LCD_CS, LCD_A0, LCD_RESET)
{
  pinMode(LCD_POWER, OUTPUT);
  digitalWrite(LCD_POWER, LOW);

  pinMode(LCD_BACKLIGHT, OUTPUT);
}

void Display::setBacklight(uint8_t state)
{
  digitalWrite(LCD_BACKLIGHT, state);
}

uint8_t Display::backlight()
{
  return digitalRead(LCD_BACKLIGHT);
}
