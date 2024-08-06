#ifndef Cloud_h
#define Cloud_h

#include "Arduino.h"
#include <FastLED.h>
#include <LittleVector.h>

#include "xy.h"
#include "drop.h"

class Cloud {
public:
  Cloud(CRGB* const led);
  void Cloud::animate();

private:
  void Cloud::drawcloud();
  void Cloud::add_drop();
  void Cloud::erase_drops();
  void Cloud::animate_drops();
  void Cloud::reset();
  CRGB* _leds;
  int8_t _x_pos;
  uint8_t _y_pos;
  Drop* _drop; 
  LittleVector<Drop*> _drops;
};

#endif