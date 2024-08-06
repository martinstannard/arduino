#include "Arduino.h"
#include <FastLED.h>
#include "drop.h"

#define DROP_COLOUR 35

Drop::Drop(CRGB* const leds, uint8_t x_start, uint8_t y_start) {
  _x_pos = x_start;
  _y_pos = y_start;
  _leds = leds;
}

void Drop::animate() {
  _leds[XYsafe(_x_pos, _y_pos)] = CHSV(DROP_COLOUR, 255, 255);
  _y_pos--;
}