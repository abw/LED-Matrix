// Second test of LED Matrix using FastLED library
// This adds the LEDMatrix to map (x,y) to LEDs
#include <FastLED.h>
#include "LEDMatrix.hpp"

// constants for width, height, pins, etc.
const unsigned int ledPin  = 12;
const unsigned int width   = 24;
const unsigned int height  = 18;
const unsigned int numLeds = width * height;
const unsigned int pause   = 10;

// create storage buffer for LED state
CRGB leds[numLeds];

// create new matrix
LEDMatrix matrix(leds, width, height, BottomRight, RowsSnake);

void setup() {
    // register LEDs with FastLED library
    FastLED.addLeds<NEOPIXEL, ledPin>(leds, numLeds);
}

void walkRGB(
    uint8_t red, uint8_t green, uint8_t blue
) {
    // iterate y from 0 to height
    for (int y = 0; y < height; y++) {
        // iterate x from 0 to width
        for (int x = 0; x < width; x++) {
            // set pixel colour
            matrix.led(x, y).setRGB(red, green, blue);
            // send LED data to the hardware
            FastLED.show();
            // turn it off for the next loop iteration
            matrix.led(x, y).setRGB(0, 0, 0);
            // rest a while and enjoy the view
            delay(pause);
        }
    }
}

void loop() {
    walkRGB(255, 0, 0);  // red
    walkRGB(0, 255, 0);  // green
    walkRGB(0, 0, 255);  // blue
}
