//---------------------------------------------------------------------
// SignWriter.hpp
//
// Subclass of TrailBlazer to render text
//
// Written by Andy Wardley <abw@wardley.org> February 2018
//---------------------------------------------------------------------

#ifndef SIGNWRITER_HPP
#define SIGNWRITER_HPP
#include "LEDMatrix.hpp"
#include "TrailBlazer.hpp"

const uint8_t charHeight = 12;
const uint8_t charWidth  =  8;
const uint8_t char4[charHeight] = {
    6, 6, 255, 255, 198, 102, 102, 54, 30, 30, 14, 6
};

class SignWriter : public TrailBlazer {
public:
    SignWriter(LEDMatrix *matrix);
    virtual void render(
        uint8_t x, uint8_t y,
        uint8_t hue, uint8_t sat, uint8_t val
    );
};

#endif
