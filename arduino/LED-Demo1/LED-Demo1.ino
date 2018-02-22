#include <FastLED.h>
#include "LEDMatrix.hpp"
//#include "Point.hpp"
#include "Cursor.hpp"
#include "Button.hpp"
#include "SignWriter.hpp"

#define DEBUG_SERIAL 1

// Define the LED matrix as (width, height)
const unsigned int ledPin  = 12;
const unsigned int width   = 24;
const unsigned int height  = 18;
const unsigned int numLeds = width * height;
CRGB leds[width * height];
LEDMatrix matrix(leds, width, height, BottomRight, RowsSnake);

// Define the four buttons with integrated LEDs, each has a switch pin
// (input) and LED pin (output).  The latter (i.e. 3, 5, 6 and 9) must
// be PWM capable.  The third argument is the overall brightness from 0
// to 1.  The fourth argument is phase (0-1).  Set to the same value
// to have the LEDs flash in phase or to different values for out of phase.
// The fifth argument indicates if the button is active.
Button redButton(2, 3, 0.7, 0, false);
Button greenButton(4, 5, 0.6, 0, true);
Button blueButton(7, 6, 1.0, 0, false);  // yes, these pins are supposed to be out of order!
Button whiteButton(8, 9, 1.0, 0, false);

// create a list of pointers to the buttons so we can iterate over them
const int numButtons = 4;
Button *buttons[numButtons] = {
    &redButton, &greenButton, &blueButton, &whiteButton
};

// a cursor is a snake-like path that moves around the array
Cursor cursor(
    &matrix,
    0, 8,               // start position x, y
    31, 11,             // velocity vector x, y
    Reflect, Reflect,   // edge handling x, y
    48                  // trail length
);
//Cursor cursor(
//    &matrix,
//    11, 3,         // start position x, y
//    -12, 0,        // velocity vector x, y
//    Wrap, Wrap,    // edge handling x, y
//    1              // trail length
//);
// a trailblazer is a bit of code to render the cursor trail to the LEDs
TrailBlazer blazer(&matrix);
// a signwriter is a subclass of TrailBlazer to test text rendering
//SignWriter writer(&matrix);

// I can't think of a better name for this variable that determines the
// maximum speed of the cursor.  The maximum range of movement (pixels
// per second) is this factor multipled by the width and/or height as
// appropriate.  This is then shift down half way to give a negative
// or positive range of half that value.  So for a 24 x 18 array with
// maxFactor set to 6, the maximum range would be -72 to +72 (3 x 24 = 72)
// in the x direction and -54 to +54 (3 x 18)  in the y direction.
const unsigned int maxFactor = 6;

// global state variables
unsigned long start;      // milliseconds start time
double time;              // floating point seconds elapsed
bool running = false;

// function prototypes;
void startup(Button *b);
unsigned int checkButtons();
void pulseButtons(double time);
void blackout();
void pushRed(Button *b);
void pushGreen(Button *b);
void pushBlue(Button *b);
void pushWhite(Button *b);

void setup() {
    // initialise FastLED
    pinMode(ledPin, OUTPUT);
    FastLED.addLeds<NEOPIXEL, ledPin>(leds, numLeds);

    // blackout the LEDs in case any have retained their memory
    blackout();

    // In my implementation the unit goes into standby mode when first
    // turned on with only the green button active (see fifth arguments
    // where buttons are created above).  When the green button is pressed
    // the other buttons are activated and the LED patterns display.
    greenButton.onPress(startup);

#if DEBUG_SERIAL
    Serial.begin(9600);
    Serial.println("setup");
#endif
}

void startup(Button *b) {
    // activate the three buttons that are inactive
    redButton.activate();
    blueButton.activate();
    whiteButton.activate();

    // register handlers for button pushed (just test code for now)
    redButton.onPress(pushRed);
    greenButton.onPress(pushGreen);
    blueButton.onPress(pushBlue);
    whiteButton.onPress(pushWhite);

    running = true;
    start = millis();
    time = 0;

#if DEBUG_SERIAL
    Serial.println("startup");
#endif
}

void loop() {
    unsigned long now = millis() - start;
    time = (double) now / 1000;

    if (running) {
        // animate here
        cursor.move(time);
        cursor.blaze(&blazer);
        //cursor.blaze(&writer);
        FastLED.show();
    }

    checkButtons();
    pulseButtons(time);
}


unsigned int checkButtons() {
    int updated = 0;

    for (int i = 0; i < numButtons; i++) {
        updated += buttons[i]->check();
    }
    return updated;
}

void pulseButtons(double time) {
    for (int i = 0; i < numButtons; i++) {
        buttons[i]->pulse(time);
    }
}

void blackout() {
    matrix.screenRGB(0, 0, 0);
    FastLED.show();
}

void pushRed(Button *b) {
#if DEBUG_SERIAL
    Serial.println("Push Red");
#endif
    cursor.changeDirection(-12, 0);
}

void pushGreen(Button *b) {
#if DEBUG_SERIAL
    Serial.println("Push Green");
#endif
    cursor.changeDirection(0, 9);
}

void pushBlue(Button *b) {
#if DEBUG_SERIAL
    Serial.println("Push Blue");
#endif
    cursor.changeDirection(5, 3);
}

void pushWhite(Button *b) {
#if DEBUG_SERIAL
    Serial.println("Push White");
#endif
    cursor.changeDirection(
        (double) (rand() % (width  * maxFactor)) - (width  * maxFactor / 2),
        (double) (rand() % (height * maxFactor)) - (height * maxFactor / 2)
    );
}
