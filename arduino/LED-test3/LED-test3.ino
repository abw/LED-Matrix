// Second test of LED Matrix using FastLED library
// This adds the LEDMatrix to map (x,y) to LEDs
#include <FastLED.h>
#include "LEDMatrix.hpp"
#include "Button.hpp"

// constants for width, height, pins, etc.
const unsigned int ledPin     = 12;
const unsigned int width      = 18;
const unsigned int height     = 24;
const unsigned int numLeds    = width * height;
const unsigned int numButtons = 4;
const unsigned int pause      = 10;

// create storage buffer for LED state
CRGB leds[numLeds];

// create new matrix
// LEDMatrix matrix(leds, width, height, BottomRight, RowsSnake);
LEDMatrix matrix(leds, width, height, TopRight, ColsSnake);

// define the buttons, each has an input pin and an LED pin
Button redButton(2, 3);
Button greenButton(4, 5);
Button blueButton(7, 6);
Button whiteButton(8, 9);

// create a list of pointers to the buttons so we can iterate over them
Button *buttons[numButtons] = {
    &redButton, &greenButton, &blueButton, &whiteButton
};

// other global state variables
unsigned long start;      // milliseconds start time
CRGB colour = CRGB::Red;  // LED matrix colour

// function prototypes
unsigned int checkButtons();
void pushRed(Button *b);
void pushGreen(Button *b);
void pushBlue(Button *b);
void pushWhite(Button *b);

void setup() {
    // register LEDs with FastLED library
    FastLED.addLeds<NEOPIXEL, ledPin>(leds, numLeds);

    // register handlers for button pushes
    redButton.onPress(pushRed);
    greenButton.onPress(pushGreen);
    blueButton.onPress(pushBlue);
    whiteButton.onPress(pushWhite);

    // mark the start time
    start = millis();
}

void loop() {
    walk();
}

void walk() {
    // iterate over each LED
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // turn it on, turn it on again...
            *(matrix.led(x, y)) = colour;
            FastLED.show();
            // turn it off for the next loop iteration
            matrix.led(x, y)->setRGB(0, 0, 0);
            // rest a while and enjoy the view
            delay(pause);
            // then check the buttons
            checkButtons();
            // and pulse the LEDs in the button bezels
            pulseButtons();
        }
    }
}

unsigned int checkButtons() {
    int updated = 0;

    for (int i = 0; i < numButtons; i++) {
        updated += buttons[i]->check();
    }
    return updated;
}

void pushRed(Button *b) {
    colour = CRGB::Red;
}

void pushGreen(Button *b) {
    colour = CRGB::Green;
}

void pushBlue(Button *b) {
    colour = CRGB::Blue;
}

void pushWhite(Button *b) {
    colour = CRGB::White;
}

void pulseButtons() {
    unsigned long now = millis() - start;
    double time = (double) now / 1000;
    for (int i = 0; i < numButtons; i++) {
        buttons[i]->pulse(time);
    }
}
