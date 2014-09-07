#include "U8glib.h"
#include "UniversalButtons.h"

#include "pins_mke.h"

#include "Display.h"
#include "Leds.h"

Display display;
/* Leds leds; */
UniversalButtons buttons;

void setup(void)
{
  SerialUSB.begin(115200);
  SerialUSB.println("Cirno");

  display.setBacklight(LCD_BACKLIGHT_ON);

  // Configure GLCD font
  display.glcd.setFont(u8g_font_6x10);
  display.glcd.setFontRefHeightExtendedText();
  display.glcd.setDefaultForegroundColor();
  display.glcd.setFontPosTop();

  // Configure buttons
  buttons.setStateChangeCallback(&button_handler);
  buttons.addButton(BUTTON_LIGHT);
  buttons.addButton(BUTTON_SCREEN_RIGHT);
  buttons.addButton(BUTTON_SCREEN_LEFT);
  buttons.addButton(BUTTON_A);
  buttons.addButton(BUTTON_B);
  buttons.addButton(BUTTON_UP);
  buttons.addButton(BUTTON_RIGHT);
  buttons.addButton(BUTTON_DOWN);
  buttons.addButton(BUTTON_LEFT);
  buttons.addButton(BUTTON_CENTER);
}

void loop()
{
  buttons.poll();

  // Display some text on the GLCD
  display.glcd.firstPage();
  do
  {
    display.glcd.drawStr(10, 20, "Hello, World!");
  }
  while(display.glcd.nextPage());

  delay(10);
}

/**
 * Basic handler for button state changes.
 */
void button_handler(buttonid_t id, uint8_t state)
{
  SerialUSB.print("Button ");
  SerialUSB.print(id);
  if(state)
    SerialUSB.println(" pressed.");
  else
    SerialUSB.println(" released.");
}
