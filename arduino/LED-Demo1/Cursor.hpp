//---------------------------------------------------------------------
// Cursor.hpp
//
// Represent a cursor position in a matrix
//
// Written by Andy Wardley <abw@wardley.org> February 2018
//---------------------------------------------------------------------

#ifndef CURSOR_HPP
#define CURSOR_HPP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "LEDMatrix.hpp"
//#include "Point.hpp"
#include "TrailBlazer.hpp"

class Cursor {
public:
    Cursor(
        LEDMatrix *matrix,
        long xorg, long yorg, double dx, double dy,
        LEDMatrixBounds foldX=Wrap, LEDMatrixBounds foldY=Wrap,
        unsigned int trail=0
    );
    void debug();
    void debugMatrix();
    void start(double time);
    bool move(double time);
    void changeDirection(double dx, double dy);
    void blaze(TrailBlazer *tb);

    ~Cursor();
private:
    LEDMatrix *_matrix;
    long   _xorg;
    long   _yorg;
    double _dx;
    double _dy;
    LEDMatrixBounds   _foldX;
    LEDMatrixBounds   _foldY;
    bool   _reflectY;
    unsigned int _width;    // width of matrix
    unsigned int _height;   // height of matrix
    unsigned int _trail;    // length of trail
    unsigned int _size;     // total size (memory allocated) of points for head + trail
    unsigned int _length;   // current length of trail
    unsigned int _head;     // index of head element
    double _start;          // start time
    double _time;           // last animation time
    Point *_points;
};

#endif
