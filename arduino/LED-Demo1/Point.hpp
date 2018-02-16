//---------------------------------------------------------------------
// Point.hpp
//
// Represent a point in a matrix as an (x, y) pair
//
// Written by Andy Wardley <abw@wardley.org> February 2018
//---------------------------------------------------------------------

#ifndef POINT_HPP
#define POINT_HPP

typedef struct {
    unsigned int x;
    unsigned int y;
} Point;

void setPoint(Point *p, unsigned int x, unsigned int y);
bool eqPoint(Point *a, Point *b);

#endif
