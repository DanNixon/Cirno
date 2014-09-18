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
 * @param delimiter Character to delimit text on
 */
void TiLDA_MKe::drawWrappedStr(uint8_t x, uint8_t y,
    uint8_t w, uint8_t h, char *text, char delimiter)
{
  char *last_newline_ptr = text;
  uint8_t y_increment = glcd.getFontLineSpacing();
  uint8_t pos_y = y + y_increment;

  while(*last_newline_ptr != '\0')
  {
    char *cut_point = getNewlinePtr(last_newline_ptr+1, w, delimiter);
    int16_t len = cut_point - last_newline_ptr;
    char *sub_str = new char[len + 1];

    char *copy_start = last_newline_ptr;
    if(*copy_start == delimiter)
      ++copy_start;

    memcpy(sub_str, copy_start, len);
    sub_str[len] = '\0';

    glcd.drawStr(x, pos_y, sub_str);

    delete[] sub_str;

    last_newline_ptr = cut_point;
    pos_y += y_increment;

    if(pos_y - y > h)
      return;
  }
}

/**
 * Determines if a string is too long to fit in a certain pixel width.
 *
 * @param string Pointer to the string
 * @param len Length of the sub string
 * @param limit Width in pixels the text must be less than
 * @return True if the substring is wider then limit
 */
bool TiLDA_MKe::subStringOverLength(char *string, uint8_t len, uint8_t limit)
{
  char *sub_str = new char[len + 1];
  memcpy(sub_str, string, len);
  sub_str[len] = '\0';
  uint8_t width = glcd.getStrWidth(sub_str);
  delete[] sub_str;
  return width > limit;
}

/**
 * Gets a pointer to the position to wrap text for the GLCD.
 *
 * @param string String pointer
 * @param width Max. text width in pixels
 * @param delimiter Char. to delimit text on
 * @return Pointer where the text should be split
 */
char *TiLDA_MKe::getNewlinePtr(char *string, uint8_t width, char delimiter)
{
  uint8_t len = 1;
  bool over_length = false;

  while(len < strlen(string))
  {
    if(subStringOverLength(string, len, width))
    {
      over_length = true;
      break;
    }
    len++;
  }

  if(over_length)
  {
    while(len > 0)
    {
      if(string[len] == delimiter)
        return string+len;

      len--;
    }
  }
  else
  {
    return string+len;
  }
}
