#include "xy.h"

// Params for width and height
const uint8_t kMatrixWidth = 16;
const uint8_t kMatrixHeight = 16;

// Param for different pixel layouts
const bool kMatrixSerpentineLayout = true;
const bool kMatrixVertical = false;

uint16_t XYsafe(uint8_t x, uint8_t y) {
  if (x >= kMatrixWidth) return -1;
  if (y >= kMatrixHeight) return -1;
  return XY(x, y);
}

uint16_t XY(uint8_t x, uint8_t y) {
  uint16_t i;

  if (kMatrixSerpentineLayout == false) {
    if (kMatrixVertical == false) {
      i = (y * kMatrixWidth) + x;
    } else {
      i = kMatrixHeight * (kMatrixWidth - (x + 1)) + y;
    }
  }

  if (kMatrixSerpentineLayout == true) {
    if (kMatrixVertical == false) {
      if (y & 0x01) {
        // Odd rows run backwards
        uint8_t reverseX = (kMatrixWidth - 1) - x;
        i = (y * kMatrixWidth) + reverseX;
      } else {
        // Even rows run forwards
        i = (y * kMatrixWidth) + x;
      }
    } else {  // vertical positioning
      if (x & 0x01) {
        i = kMatrixHeight * (kMatrixWidth - (x + 1)) + y;
      } else {
        i = kMatrixHeight * (kMatrixWidth - x) - (y + 1);
      }
    }
  }

  return i;
}
