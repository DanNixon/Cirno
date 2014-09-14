/**
 * Demonstrates the text wrapping function.
 */

#include "U8glib.h"
#include "UniversalButtons.h"

#include "TiLDA_MKe.h"

TiLDA_MKe tilda;

void setup(void)
{
  SerialUSB.begin(115200);
  SerialUSB.println("Cirno");

  tilda.setBacklight(LCD_BACKLIGHT_ON);

  // Set button callback
  tilda.buttons.setStateChangeCallback(&button_handler);

  // Light the RGB LEDs
  tilda.setLED(1, 0, 5, 10);
  tilda.setLED(2, 0, 5, 10);
}

void loop()
{
  // See if there were any button changes
  tilda.buttons.poll();

  // Display some text on the GLCD
  tilda.glcd.firstPage();
  do
  {
    char *longString = "This is a quite long string, far too long to be printed on a single line of a GLCD";
    tilda.glcd.setFont(u8g_font_6x10);
    tilda.printWrappedString(10, 0, 80, 64, longString);
  }
  while(tilda.glcd.nextPage());

  delay(10);
}

/**
 * Basic handler for button state changes.
 */
void button_handler(buttonid_t id, uint8_t state)
{
  // Toggle backlight on pressing Light button
  if(state && (id == BUTTON_LIGHT))
    tilda.toggleBacklight();
}
