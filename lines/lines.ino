/// @file    newcloud.ino
/// @brief   raindrops

#include <FastLED.h>
#include "xy.h"
#include <LittleVector.h>

#define DATA_PIN 9

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
  fadeall(250);
  Line line = bresenhamLine(random8(16), random8(16), random8(16), random8(16));
  if (random(10) == 0) {drawline(line);}
  FastLED.show();

  delay(10);

  // display_freeram();
}

void drawline(Line points) {
  uint8_t hue = random8(255);
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
