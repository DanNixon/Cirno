#include "Leds.h"

#include "Arduino.h"
#include "pins_mke.h"

Leds::Leds()
{
  pinMode(LED1_RED, OUTPUT);
  pinMode(LED1_GREEN, OUTPUT);
  pinMode(LED1_BLUE, OUTPUT);

  pinMode(LED2_RED, OUTPUT);
  pinMode(LED2_GREEN, OUTPUT);
  pinMode(LED2_BLUE, OUTPUT);
}

void Leds::setLED(uint8_t led, uint8_t r, uint8_t g, uint8_t b)
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
