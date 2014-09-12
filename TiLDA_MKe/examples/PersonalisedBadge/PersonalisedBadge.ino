/**
 * The hung screen I used on my TiLDA during EMF.
 * In case I ever want to use it as an overengineered badge again.
 */

#include "U8glib.h"
#include "UniversalButtons.h"

#include "TiLDA_MKe.h"

TiLDA_MKe tilda;
bool torch = false;

void setup(void)
{
  tilda.setBacklight(LCD_BACKLIGHT_ON);

  // Set button callback
  tilda.buttons.setStateCycleCallback(&button_handler);
}

void loop()
{
  // See if there were any button changes
  tilda.buttons.poll();

  // Display some text on the GLCD
  tilda.glcd.firstPage();
  do
  {
    tilda.glcd.setRot270();

    tilda.glcd.setFont(u8g_font_helvB12);
    tilda.glcd.setFontPosTop();
    tilda.glcd.drawStr(0, 0, "Dan");
    tilda.glcd.drawStr(0, 15, "Nixon");

    tilda.glcd.setFont(u8g_font_5x7);
    tilda.glcd.setFontPosTop();
    tilda.glcd.drawStr(0, 32, "dan-nixon.com");
    tilda.glcd.drawStr(0, 42, "@technoducky");

    tilda.glcd.setFont(u8g_font_6x10);
    tilda.glcd.setFontPosTop();
    tilda.glcd.drawStr(0, 60, "Code");
    tilda.glcd.drawStr(0, 70, "moneky,");
    tilda.glcd.drawStr(0, 80, "electronics");
    tilda.glcd.drawStr(0, 90, "engineer,");
    tilda.glcd.drawStr(0, 100, "mad");
    tilda.glcd.drawStr(0, 110, "scientist.");
  }
  while(tilda.glcd.nextPage());
}

/**
 * Basic handler for button state changes.
 */
void button_handler(buttonid_t id, uint32_t time)
{
  switch(id)
  {
    // Toggle backlight on Light
    case BUTTON_LIGHT:
      tilda.toggleBacklight();
      break;

    // Toggle LEDs on B
    case BUTTON_B:
      torch = !torch;

      if(torch)
        tilda.setLEDs(255, 255, 255);
      else
        tilda.setLEDs(0, 0, 0);

      break;
  }
}
