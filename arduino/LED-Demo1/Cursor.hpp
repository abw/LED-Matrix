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
#include <math.h>
#include <vector>
#include "LEDMatrix.hpp"
#include "Point.hpp"

enum CursorFold { Wrap, Reflect };
const double epsilon = 0.0001;

class Cursor {
public:
    Cursor(
        LEDMatrix *matrix,
        long xorg, long yorg, double dx, double dy,
        CursorFold foldX=Wrap, CursorFold foldY=Wrap,
        unsigned int trail=0
    );
    void debug();
    void move(double time);
    ~Cursor();
private:
    LEDMatrix *_matrix;
    long   _xorg;
    long   _yorg;
    double _dx;
    double _dy;
    bool   _reflectX;
    bool   _reflectY;
    unsigned int _width;
    unsigned int _height;
    unsigned int _trail;
    Point _point;
    std::vector<Point> _points;
};

#endif
