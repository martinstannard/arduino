/// @file    newcloud.ino
/// @brief   raindrops

#include <FastLED.h>
#include "cloud.h"
#include "xy.h"

#define DATA_PIN 9

uint8_t size = 4;

// Define the array of leds
#define NUM_LEDS 256
CRGB leds_safety[NUM_LEDS + 1];
CRGB* const leds(leds_safety + 1);
Cloud * cloud;

void setup() {
  cloud = new Cloud(leds);
  Serial.begin(57600);
  Serial.println("resetting");
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(200);
}

void fadeall() {
  for (int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(50); }
}

void loop() {
  fadeall(); 

  cloud->animate();
  FastLED.show();
  
  delay(100);

  display_freeram();
}

void display_freeram() {
  Serial.print(F("- SRAM left: "));
  Serial.println(freeRam());
}

int freeRam() {
  extern int __heap_start,*__brkval;
  int v;
  return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int) __brkval);  
}

