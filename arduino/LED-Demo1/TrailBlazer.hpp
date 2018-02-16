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
    void blaze(
        unsigned int i, unsigned int length,
        unsigned int x, unsigned int width,
        unsigned int y, unsigned int height,
        double time
    );
private:
    LEDMatrix *_matrix;
};

#endif
