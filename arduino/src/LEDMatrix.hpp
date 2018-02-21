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
enum LEDMatrixBounds { Wrap, Reflect };
const double epsilon = 0.0001;

typedef struct {
    unsigned int x;
    unsigned int y;
} Point;

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
    unsigned int x(double fx, LEDMatrixBounds bounds=Wrap);
    unsigned int y(double fy, LEDMatrixBounds bounds=Wrap);
    Point xy(double fx, double fy, LEDMatrixBounds xbounds=Wrap, LEDMatrixBounds ybounds=Wrap);
    CRGB *led(unsigned int x, unsigned int y);
    ~LEDMatrix();
    void screenRGB(uint8_t red, uint8_t green, uint8_t blue);
    void init();
private:
    CRGB *_leds;
    unsigned int _width;
    unsigned int _height;
    unsigned int _size;
    uint16_t *_xymap;
    LEDMatrixOrigin _origin;
    LEDMatrixOrient _orient;
};

#endif
