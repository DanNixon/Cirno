/**
 * Sample with usage of basic features.
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
    if(tilda.buttons.getButtonState(BUTTON_LIGHT))
      tilda.glcd.drawStr(0, 40, "Light");
    if(tilda.buttons.getButtonState(BUTTON_A))
      tilda.glcd.drawStr(0, 40, "A");
    if(tilda.buttons.getButtonState(BUTTON_B))
      tilda.glcd.drawStr(0, 40, "B");
    if(tilda.buttons.getButtonState(BUTTON_UP))
      tilda.glcd.drawStr(0, 40, "Up");
    if(tilda.buttons.getButtonState(BUTTON_DOWN))
      tilda.glcd.drawStr(0, 40, "Down");
    if(tilda.buttons.getButtonState(BUTTON_LEFT))
      tilda.glcd.drawStr(0, 40, "Left");
    if(tilda.buttons.getButtonState(BUTTON_RIGHT))
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
