/**
 * Demonstrates the text wrapping function.
 */

#include <U8glib.h>
#include <UniversalInputManager.h>
#include <IButton.h>

#include <TiLDA_MKe.h>

TiLDA_MKe tilda;

void setup(void)
{
  SerialUSB.begin(115200);
  SerialUSB.println("Cirno");

  tilda.setBacklight(LCD_BACKLIGHT_ON);

  // Set button callback
  tilda.buttons.setCallback(button_handler);

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
    char *shorterString = "Hello world";

    tilda.glcd.setFont(u8g_font_6x10);

    tilda.drawWrappedStr(10, 0, 50, 50, longString);
    tilda.glcd.drawFrame(10, 0, 50, 50);

    tilda.drawWrappedStr(0, 50, 127, 12, shorterString);
    tilda.glcd.drawFrame(0, 50, 127, 12);

    tilda.drawWrappedStr(64, 0, 63, 50, shorterString);
    tilda.glcd.drawFrame(64, 0, 63, 50);
  }
  while(tilda.glcd.nextPage());

  delay(10);
}

/**
 * Basic handler for button state changes.
 */
void button_handler(inputtype_t type, IInputDevice * device)
{
  if(type != UIT_BUTTON)
    return;

  IButton * button = (IButton *) device;

  // Toggle backlight on pressing Light button
  if(button->isActive() && (button->getID() == BUTTON_LIGHT))
    tilda.toggleBacklight();
}
