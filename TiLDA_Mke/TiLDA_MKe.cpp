#include "TiLDA_MKe.h"

#include "Arduino.h"

/* TODO */
/* LCD_POWER should really have software PWM, since it is used for contrast control */
/* It needs to be added for the LEDs anyway */

TiLDA_MKe::TiLDA_MKe() :
  glcd(LCD_CS, LCD_A0, LCD_RESET)
{
  // GLCD setup
  pinMode(LCD_POWER, OUTPUT);
  digitalWrite(LCD_POWER, LOW);

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
  /* pinMode(LED1_RED, OUTPUT); */
  /* pinMode(LED1_GREEN, OUTPUT); */
  /* pinMode(LED1_BLUE, OUTPUT); */

  /* pinMode(LED2_RED, OUTPUT); */
  /* pinMode(LED2_GREEN, OUTPUT); */
  /* pinMode(LED2_BLUE, OUTPUT); */

  /* uint8_t inital_state = HIGH; */
  /* setLED(1, inital_state, inital_state, inital_state); */
  /* setLED(2, inital_state, inital_state, inital_state); */
}

void TiLDA_MKe::setBacklight(uint8_t state)
{
  digitalWrite(LCD_BACKLIGHT, state);
}

uint8_t TiLDA_MKe::backlight()
{
  return digitalRead(LCD_BACKLIGHT);
}

void TiLDA_MKe::setLED(uint8_t led, uint8_t r, uint8_t g, uint8_t b)
{
  //TODO: Add software PWM here

  switch(led)
  {
    case 1:
      digitalWrite(LED1_RED, r);
      digitalWrite(LED1_GREEN, g);
      digitalWrite(LED1_BLUE, b);
      break;
    case 2:
      digitalWrite(LED2_RED, r);
      digitalWrite(LED2_GREEN, g);
      digitalWrite(LED2_BLUE, b);
      break;
    default:
      return;
  }
}
