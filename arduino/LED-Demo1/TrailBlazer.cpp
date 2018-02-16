#include "TrailBlazer.hpp"

TrailBlazer::TrailBlazer(
    LEDMatrix *matrix
) {
    _matrix = matrix;
}

void TrailBlazer::blaze(
    unsigned int i, unsigned int length,
    unsigned int x, unsigned int width,
    unsigned int y, unsigned int height,
    double time
) {
    double distance = (double) i / (length - 1);
    //double nhue = (double) x / width;
    double nhue = rampUpWave(time / 2 + distance / 2);
    double nsat = sin(distance * M_PI_2); // quarter cycle
    double nval = 1 - distance * distance; // * rampDownWave(distance * 4);
    nval = nval < 0 ? 0 : nval;
    unsigned int hue = 255 * nhue;
    unsigned int sat = 255 * nsat;
    unsigned int val = 255 * nval;

    //printf(
    //    "blazing %d/%d at %d,%d of %d,%d H:%d S:%d V:%d\n",
    //    i, length, x, y, width, height,
    //    hue, sat, val
    //);
    _matrix->led(x, y)->setHSV(hue, sat, val);
}
