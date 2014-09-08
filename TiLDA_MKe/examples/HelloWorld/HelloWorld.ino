#include "U8glib.h"
#include "UniversalButtons.h"

#include "TiLDA_MKe.h"

TiLDA_MKe tilda;

void setup(void)
{
  SerialUSB.begin(115200);
  SerialUSB.println("Cirno");

  tilda.setBacklight(LCD_BACKLIGHT_ON);

  // Configure GLCD font
  tilda.glcd.setFont(u8g_font_6x10);
  tilda.glcd.setFontRefHeightExtendedText();
  tilda.glcd.setDefaultForegroundColor();
  tilda.glcd.setFontPosTop();

  // Set button callback
  tilda.buttons.setStateChangeCallback(&button_handler);

  // Light the RGB LEDs
  tilda.setLED(1, 0, 0, 50);
  tilda.setLED(2, 50, 0, 0);
}

void loop()
{
  // See if there were any button changes
  tilda.buttons.poll();

  // Display some text on the GLCD
  tilda.glcd.firstPage();
  do
  {
    tilda.glcd.drawStr(0, 0, "Hello, World!");
    tilda.glcd.drawStr(5, 25, "Eye'm the strongest!");
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

  SerialUSB.print("Button ");
  SerialUSB.print(id);
  if(state)
    SerialUSB.println(" pressed.");
  else
    SerialUSB.println(" released.");
}
