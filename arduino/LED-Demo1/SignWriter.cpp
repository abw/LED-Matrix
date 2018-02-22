#include "SignWriter.hpp"

SignWriter::SignWriter(
    LEDMatrix *matrix
)
: TrailBlazer(matrix) {
    // nothing will come of nothing
}

void SignWriter::render(
    uint8_t x, uint8_t y,
    uint8_t hue, uint8_t sat, uint8_t val
) {
    unsigned int width = _matrix->width();
    unsigned int height = _matrix->height();

    //_matrix->led(x, y)->setHSV(hue, sat, val);
    //uint8_t ledx = x + charWidth - 1;
    //uint8_t ledy = y + charHeight - 1;
    //_matrix->led(ledx, ledy)->setHSV((hue + 128) % 255, sat, val);

    for (int cy = 0; cy < charHeight; cy++) {
        uint8_t mask = char4[cy];
        uint8_t factor = 128;
        for (uint8_t cx = 0; cx < charWidth; cx++) {
            if (mask & factor) {
                _matrix->led(
                    _matrix->x(x + cx, Wrap),
                    _matrix->y(y + cy, Wrap)
                ).setHSV((hue + cy * 10) % 255, sat, val);
            }
            factor = factor >> 1;
        }
    }
}
