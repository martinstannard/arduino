#ifndef Drop_h
#define Drop_h
#include "Arduino.h"
#include "xy.h"

class Drop {
public:
  Drop(CRGB* const led, uint8_t x_start, uint8_t y_start);
  void Drop::animate();

private:
  CRGB* _leds;
  uint8_t _x_pos;
  uint8_t _y_pos;
};

#endif
