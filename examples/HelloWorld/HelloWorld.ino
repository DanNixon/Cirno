/**
 * Sample with usage of basic features.
 */

#include "U8glib.h"
#include "UniversalInputManager.h"
#include "IButton.h"

#include "TiLDA_MKe.h"

TiLDA_MKe tilda;

void setup(void)
{
  SerialUSB.begin(115200);
  SerialUSB.println("Cirno");

  tilda.setBacklight(LCD_BACKLIGHT_ON);

  // Set button callback
  tilda.buttons.setCallback(button_handler);

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
    tilda.glcd.setFont(u8g_font_6x10);
    tilda.glcd.drawStr(0, 7, "Hello, World!");
    tilda.glcd.drawStr(5, 25, "Eye'm the strongest!");

    // Show some button info
    tilda.glcd.setFont(u8g_font_5x7);
    if(((IButton *) tilda.buttons.getDevice(BUTTON_LIGHT))->isActive())
      tilda.glcd.drawStr(0, 40, "Light");
    if(((IButton *) tilda.buttons.getDevice(BUTTON_A))->isActive())
      tilda.glcd.drawStr(0, 40, "A");
    if(((IButton *) tilda.buttons.getDevice(BUTTON_B))->isActive())
      tilda.glcd.drawStr(0, 40, "B");
    if(((IButton *) tilda.buttons.getDevice(BUTTON_UP))->isActive())
      tilda.glcd.drawStr(0, 40, "Up");
    if(((IButton *) tilda.buttons.getDevice(BUTTON_DOWN))->isActive())
      tilda.glcd.drawStr(0, 40, "Down");
    if(((IButton *) tilda.buttons.getDevice(BUTTON_LEFT))->isActive())
      tilda.glcd.drawStr(0, 40, "Left");
    if(((IButton *) tilda.buttons.getDevice(BUTTON_RIGHT))->isActive())
      tilda.glcd.drawStr(0, 40, "Right");

    // Show some battery info
    char buffer[40];
    sprintf(buffer, "Battery: %d%% (chg. %d)",
        tilda.getBatteryPercentage(), tilda.isCharging());
    tilda.glcd.drawStr(0, 50, buffer);
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

  SerialUSB.print("Button ");
  SerialUSB.print(button->getID());
  if(button->isActive())
    SerialUSB.println(" pressed.");
  else
    SerialUSB.println(" released.");
}
