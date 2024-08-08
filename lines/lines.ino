/// @file    newcloud.ino
/// @brief   raindrops

#include <FastLED.h>
#include "xy.h"
#include <LittleVector.h>

#define DATA_PIN 9
#define DELAY 10
#define FADE 220

// Define the array of leds
#define NUM_LEDS 256
CRGB leds_safety[NUM_LEDS + 1];
CRGB* const leds(leds_safety + 1);

// Define a point as a struct
struct Point {
  int x;
  int y;

  Point(int x, int y)
    : x(x), y(y) {}
};


using Line = LittleVector<Point>;

void setup() {
  Serial.begin(57600);
  Serial.println("resetting");
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(200);
}

void loop() {
  // leds[XYsafe(0, 0)] = CHSV(255, 255, 255);
  // leds[XYsafe(15, 0)] = CHSV(200, 255, 255);
  // leds[XYsafe(15, 15)] = CHSV(FADE, 255, 255);
  // leds[XYsafe(0, 15)] = CHSV(70, 255, 255);

  side1();
  side2();
  side3();
  side4();
  side5();
  side6();
  side7();
  side8();
  FastLED.show();
  // display_freeram();
}

void drawline(Line points) {
  uint8_t hue = 222;
  for (auto point : points) {
    leds[XYsafe(point.x, point.y)] = CHSV(hue, 255, 255);
  }
}

void display_freeram() {
  Serial.print(F("- SRAM left: "));
  Serial.println(freeRam());
}

int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

// Bresenham's Line Algorithm
Line bresenhamLine(int x0, int y0, int x1, int y1) {
  Line points;
  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);
  int sx = (x0 < x1) ? 1 : -1;
  int sy = (y0 < y1) ? 1 : -1;
  int err = dx - dy;

  while (true) {
    points.push_back({ x0, y0 });  // Add the current point to the list
    if (x0 == x1 && y0 == y1) break;
    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y0 += sy;
    }
  }

  return points;
}

void fadeall(uint8_t scale) {
  for (int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(scale); }
}

void side1() {
  for (int x = 0; x < 16; x++) {
    fadeall(FADE);
    Line line = bresenhamLine(x, 15, 0, 0);
    drawline(line);
    FastLED.show();
    delay(DELAY);
  }
}

void side2() {
  for (int y = 0; y < 16; y++) {
    fadeall(FADE);
    Line line = bresenhamLine(0, y, 15, 15);
    drawline(line);
    FastLED.show();
    delay(DELAY);
  }
}

void side3() {
  for (int y = 15; y > 0; y--) {
    fadeall(FADE);
    Line line = bresenhamLine(0, 15, 15, y);
    drawline(line);
    FastLED.show();
    delay(DELAY);
  }
}

void side4() {
  for (int x = 0; x < 15; x++) {
    fadeall(FADE);
    Line line = bresenhamLine(x, 15, 15, 0);
    drawline(line);
    FastLED.show();
    delay(DELAY);
  }
}

void side5() {
  for (int x = 15; x > 0; x--) {
    fadeall(FADE);
    Line line = bresenhamLine(15, 15, x, 0);
    drawline(line);
    FastLED.show();
    delay(DELAY);
  }
}


void side6() {
  for (int y = 15; y > 0; y--) {
    fadeall(FADE);
    Line line = bresenhamLine(15, y, 0, 0);
    drawline(line);
    FastLED.show();
    delay(DELAY);
  }
}

void side7() {
  for (int y = 0; y < 16; y++) {
    fadeall(FADE);
    Line line = bresenhamLine(0, y, 15, 0);
    drawline(line);
    FastLED.show();
    delay(DELAY);
  }
}

void side8() {
  for (int x = 15; x > 0; x--) {
    fadeall(FADE);
    Line line = bresenhamLine(0, 15, x, 0);
    drawline(line);
    FastLED.show();
    delay(DELAY);
  }
}
