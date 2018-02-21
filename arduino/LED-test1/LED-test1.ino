// Simple test of LED Matrix using FastLED library
#include <FastLED.h>

// constants for width, height, pins, etc.
const unsigned int ledPin  = 12;
const unsigned int width   = 24;
const unsigned int height  = 18;
const unsigned int numLeds = width * height;
const unsigned int pause   = 10;

// create storage buffer for LED state
CRGB leds[numLeds];

void setup() {
    // register LEDs with FastLED library
    FastLED.addLeds<NEOPIXEL, ledPin>(leds, numLeds);
}

void walkRGB(
    uint8_t red, uint8_t green, uint8_t blue
) {
    // iterate over each LED
    for (int i = 0; i < numLeds; i++) {
        // turn it on, turn it on again...
        leds[i].setRGB(red, green, blue);
        FastLED.show();
        // turn it off for the next loop iteration
        leds[i].setRGB(0, 0, 0);
        // rest a while and enjoy the view
        delay(pause);
    }
}

void loop() {
    walkRGB(255, 0, 0);  // red
    walkRGB(0, 255, 0);  // green
    walkRGB(0, 0, 255);  // blue
}
