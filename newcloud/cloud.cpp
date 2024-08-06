#include "cloud.h"

#define CLOUD_POINTS 35
#define CLOUD_COLOUR 200

const uint8_t cloud[CLOUD_POINTS][2] = {
  { 4, 2 }, { 4, 3 }, { 4, 7 }, { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 6 }, { 3, 7 }, { 3, 8 }, { 2, 0 }, { 2, 1 }, { 2, 2 }, { 2, 3 }, { 2, 4 }, { 2, 5 }, { 2, 6 }, { 2, 7 }, { 2, 8 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 1, 6 }, { 1, 7 }, { 1, 8 }, { 0, 1 }, { 0, 2 }, { 0, 3 }, { 0, 4 }, { 0, 5 }, { 0, 6 }, { 0, 7 }
};

Cloud::Cloud(CRGB* const leds) {
  _leds = leds;
  _x_pos = -10;
  _y_pos = 10;
}

void Cloud::animate() {
  reset();

  _x_pos++;

  if (random8(3) == 0) {
    add_drop();
  }

  animate_drops();
  drawcloud();
}

void Cloud::drawcloud() {
  for (int i = 0; i < CLOUD_POINTS; i++) {
    _leds[XYsafe(_x_pos + cloud[i][1], _y_pos + cloud[i][0])] = CHSV(CLOUD_COLOUR, 255, 255);
  }
}

void Cloud::add_drop() {
  _drops.push_back(new Drop(_leds, _x_pos + random8(5) + 3, 10));
}

void Cloud::erase_drops() {
  for (LittleVector<Drop*>::iterator itr = _drops.begin(); itr != _drops.end();) {
    delete *itr;
    itr = _drops.erase(itr);
  }
}

void Cloud::animate_drops() {
    for (auto drop : _drops) {

    drop->animate();
  }
}

void Cloud::reset() {
  if (_x_pos > 15) {
    _x_pos = -10;
    _y_pos = 10;
    erase_drops();
  }
}