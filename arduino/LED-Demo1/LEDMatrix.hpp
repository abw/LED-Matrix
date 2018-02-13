//---------------------------------------------------------------------
// LEDMatrix.hpp
//
// Header file containing a class for defining an LED matrix.
//
// Written by Andy Wardley <abw@wardley.org> February 2018
//---------------------------------------------------------------------

#ifndef LED_MATRIX_HPP
#define LED_MATRIX_HPP
#include <inttypes.h>
#include <stdio.h>

enum LEDMatrixOrigin { TopLeft, TopRight, BottomLeft, BottomRight   };
enum LEDMatrixOrient { RowsSnake, RowsZigZag, ColsSnake, ColsZigZag };

class LEDMatrix {
public:
    LEDMatrix(
        unsigned int width, unsigned int height,
        LEDMatrixOrigin origin=TopLeft,
        LEDMatrixOrient orient=RowsSnake
    );
    void debug();
    unsigned int width();
    unsigned int height();
    ~LEDMatrix();
    void init();
private:
    unsigned int _width;
    unsigned int _height;
    uint16_t *_leds;
    LEDMatrixOrigin _origin;
    LEDMatrixOrient _orient;
};

#endif
