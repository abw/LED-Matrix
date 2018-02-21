//---------------------------------------------------------------------
// TrailBlazer.hpp
//
// Renderer for the trail of a cursor
//
// Written by Andy Wardley <abw@wardley.org> February 2018
//---------------------------------------------------------------------

#ifndef TRAILBLAZER_HPP
#define TRAILBLAZER_HPP
#include "LEDMatrix.hpp"
#include "Waveforms.hpp"

class TrailBlazer {
public:
    TrailBlazer(LEDMatrix *matrix);
    virtual void blaze(
        unsigned int i, unsigned int length,
        unsigned int x, unsigned int width,
        unsigned int y, unsigned int height,
        double time
    );
    virtual void render(
        uint8_t x, uint8_t y,
        uint8_t hue, uint8_t sat, uint8_t val
    );
protected:
    LEDMatrix *_matrix;
};

#endif
