//---------------------------------------------------------------------
// LEDMatrix.hpp
//
// Header file containing a class for defining an LED matrix.
//
// Written by Andy Wardley <abw@wardley.org> February 2018
//---------------------------------------------------------------------

#ifndef LED_MATRIX_HPP
#define LED_MATRIX_HPP
#include <FastLED.h>
#include <inttypes.h>
#include <stdio.h>

enum LEDMatrixOrigin { TopLeft, TopRight, BottomLeft, BottomRight   };
enum LEDMatrixOrient { RowsSnake, RowsZigZag, ColsSnake, ColsZigZag };

class LEDMatrix {
public:
    LEDMatrix(
        CRGB *fastleds,
        unsigned int width, unsigned int height,
        LEDMatrixOrigin origin=TopLeft,
        LEDMatrixOrient orient=RowsSnake
    );
    void debug();
    unsigned int width();
    unsigned int height();
    CRGB *led(unsigned int x, unsigned int y);
    ~LEDMatrix();
    void screenRGB(uint8_t red, uint8_t green, uint8_t blue);
    void init();
private:
    CRGB *_fastleds;
    unsigned int _width;
    unsigned int _height;
    unsigned int _size;
    uint16_t *_leds;
    LEDMatrixOrigin _origin;
    LEDMatrixOrient _orient;
};

#endif
