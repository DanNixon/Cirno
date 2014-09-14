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
 * @param x X coordinate of the top left corner of the area
 * @param y Y coordinate of the top left corner of the area
 * @param w Width of the area
 * @param h Height of the area
 * @param text Text string
 * @param delimitOn Character to delimit text on
 */
void TiLDA_MKe::drawWrappedStr(uint8_t x, uint8_t y,
    uint8_t w, uint8_t h, char *text, char delimitOn)
{
  glcd.setFontPosBaseline();

  int last_cut_index = 0;
  int prev_cut_index = 0;
  int cut_index = 0;
  int num_rows = 1;

  while(last_cut_index < strlen(text))
  {
    char *search_start = text + prev_cut_index + 1;
    char *string_start = text + last_cut_index + 1;
    char *space_index = strchr(search_start, delimitOn);
    cut_index = space_index - text;

    int y_pos = y + ((glcd.getFontAscent() + abs(glcd.getFontDescent())) * num_rows);

    // At the end of the string, just print it
    if(space_index == NULL)
    {
      char *out_text = search_start;
      if(num_rows == 1)
        out_text = string_start - 1;

      if(y_pos <= (y + w))
      {
        glcd.drawStr(x, y_pos - glcd.getFontDescent(), out_text);
        num_rows++;
      }
      break;
    }

    // Create substring
    char sub_str[cut_index - last_cut_index];
    memcpy(sub_str, string_start, cut_index-last_cut_index);
    sub_str[cut_index - last_cut_index] = '\0';

    // Test substring
    if(glcd.getStrWidth(sub_str) < w)
    {
      prev_cut_index = cut_index;
    }
    else
    {
      if(prev_cut_index == 0)
        prev_cut_index = cut_index;

      // Get string to be printed
      char print_str[prev_cut_index - last_cut_index + 1];
      char *out_string_start = string_start;

      if(*(text+last_cut_index) != delimitOn)
        out_string_start--;

      memcpy(print_str, out_string_start, prev_cut_index-last_cut_index);

      print_str[prev_cut_index - last_cut_index] = '\0';
      last_cut_index = prev_cut_index;

      if(y_pos <= (y + w))
      {
        glcd.drawStr(x, y_pos - glcd.getFontDescent(), print_str);
        num_rows++;
      }
      else
        break;
    }
  }
}
