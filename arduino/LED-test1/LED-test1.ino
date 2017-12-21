#include <FastLED.h>

#define NUM_COLS   24
#define NUM_ROWS   18
#define NUM_LEDS (NUM_COLS * NUM_ROWS)
#define LED_PIN     6
#define PAUSE      10 

CRGB leds[NUM_LEDS];

void setup() {
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
}

void walkRGB(uint8_t red, uint8_t green, uint8_t blue, uint8_t pause) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].setRGB(red, green, blue);
        FastLED.show();
        leds[i].setRGB(0, 0, 0);
        delay(pause);
    }
}

void loop() {
    walkRGB(255, 0, 0, PAUSE);
    walkRGB(0, 255, 0, PAUSE);
    walkRGB(0, 0, 255, PAUSE);
}
