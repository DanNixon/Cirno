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
}

void loop()
{
  tilda.buttons.poll();

  // Display some text on the GLCD
  tilda.glcd.firstPage();
  do
  {
    tilda.glcd.drawStr(10, 20, "Hello, World!");
  }
  while(tilda.glcd.nextPage());

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
