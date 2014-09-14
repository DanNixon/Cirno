#include "TiLDA_MKe.h"

#include "Arduino.h"

TiLDA_MKe::TiLDA_MKe() :
  glcd(LCD_CS, LCD_A0, LCD_RESET)
{
  // GLCD setup
  pinMode(LCD_POWER, OUTPUT);
  digitalWrite(LCD_POWER, LOW);

  /*
   * I think the EMF board def. puts this on a PWM pin
   * but keeping it on digital makes it easier to toggle
   */
  pinMode(LCD_BACKLIGHT, OUTPUT);

  // Configure buttons
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

  // LED setup
  setLEDs(0, 0, 0);

  // Battery monitor setup
  pinMode(MCP_STAT, INPUT_PULLUP);
  pinMode(VBATT_MON, INPUT);
}

/**
 * Sets the state of the backlight.
 *
 * @param state State to set backlight to (1 or 0)
 */
void TiLDA_MKe::setBacklight(uint8_t state)
{
  digitalWrite(LCD_BACKLIGHT, state);
}

/**
 * Gets the state of the backlight.
 *
 * @returns Backlight state
 */
uint8_t TiLDA_MKe::backlight()
{
  return digitalRead(LCD_BACKLIGHT);
}

/**
 * Flips the state of the backlight then returns the new state.
 *
 * @returns New backlight state
 */
uint8_t TiLDA_MKe::toggleBacklight()
{
  digitalWrite(LCD_BACKLIGHT, !backlight());
  return backlight();
}

/**
 * Sets the colour and brightness of the RGB LEDs.
 *
 * @param led LED to set (1 or 2)
 * @param r Red intensity
 * @param g Green intensity
 * @param b Blue intensity
 */
void TiLDA_MKe::setLED(uint8_t led, uint8_t r, uint8_t g, uint8_t b)
{
  switch(led)
  {
    case 1:
      analogWrite(LED1_RED, r);
      analogWrite(LED1_GREEN, g);
      analogWrite(LED1_BLUE, b);
      break;
    case 2:
      analogWrite(LED2_RED, r);
      analogWrite(LED2_GREEN, g);
      analogWrite(LED2_BLUE, b);
      break;
    default:
      return;
  }
}

/**
 * Sets both RGB LEDs to the same colour.
 *
 * @param r Red intensity
 * @param g Green intensity
 * @param b Blue intensity
 */
void TiLDA_MKe::setLEDs(uint8_t r, uint8_t g, uint8_t b)
{
  setLED(1, r, g, b);
  setLED(2, r, g, b);
}

/**
 * Gets an approximation of the battery percentage.
 *
 * Note that the value is only accurate when not charging.
 *
 * @return Approx battery percentage
 */
uint8_t TiLDA_MKe::getBatteryPercentage()
{
  return (analogRead(VBATT_MON) - PMIC_BATTERY_FLAT) * PMIC_BATTERY_PERCENT_RATIO;
}

/**
 * Gets the battery voltage.
 *
 * @return Battery voltage
 */
float TiLDA_MKe::getBatteryVoltage()
{
  return (analogRead(VBATT_MON) * (3.3 / 512));
}

/**
 * Tests if the batter is being charged.
 *
 * @return True if charging, false otherwise
 */
bool TiLDA_MKe::isCharging()
{
  return !digitalRead(MCP_STAT);
}

/**
 * Prints a block of text in a given area, wrapping on a given character.
 *
 * @param x1 X coordinate of the top left corner of the area
 * @param y1 Y coordinate of the top left corner of the area
 * @param x2 X coordinate of the bottom right corner of the area
 * @param y2 Y coordinate of the bottom right corner of the area
 * @param text Text string
 * @param delimitOn Character to delimit text on
 *
 * @returns Number of characters in text string that could not be made to fit in given area
 */
size_t TiLDA_MKe::printWrappedString(uint8_t x1, uint8_t y1,
    uint8_t x2, uint8_t, y2, char *text, char delimitOn)
{

  return 0;
}
