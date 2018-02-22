#include "TrailBlazer.hpp"

#define DEBUG_SERIAL 0

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
    double dw = (double) x / width;
    double dh = (double) y / height;
    double nhue = rampUpWave(time / 2);
    //double nsat = i > 0 ? 1 : 0; //sin(distance * M_PI_2); // quarter cycle
    double nsat = sin(distance * M_PI_2); // quarter cycle
    double nval = 1 - distance * distance; // * rampDownWave(distance * 4);
    //nval = nval == 0 ? 0.05 : nval;
    if (nval == 0) {
        nval = sinWave(dw * 4 + dh) * 0.2 + 0.05;
        nsat  = 1 - sinWave(dh * 3 + dw) * 0.8;
        dw -= 0.5;
        dh -= 0.5;
        nhue  = fmod(sqrt(dw*dw + dh*dh) * 2, 1);
        nsat  = 1 - fmod(sqrt(dw*dw + dh*dh) * 4, 1) * 0.5;
        nsat  = 1;
    }
    uint8_t hue = (uint8_t)(nhue * 255);
    uint8_t sat = (uint8_t)(nsat * 255);
    uint8_t val = (uint8_t)(nval * 255);
#if DEBUG_SERIAL
    Serial.print("i:");
    Serial.print(i);
    Serial.print("  dh:");
    Serial.print(dh);
    Serial.print("  nhue:");
    Serial.print(nhue);
    Serial.print("  hue:");
    Serial.print(hue);
    Serial.print("  nsat:");
    Serial.print(nsat);
    Serial.print("  sat:");
    Serial.println(sat);
    Serial.print("  nval:");
    Serial.print(val);
    Serial.print("  val:");
    Serial.println(val);
#endif

    this->render(x, y, hue, sat, val);
}

void TrailBlazer::render(
    uint8_t x, uint8_t y,
    uint8_t hue, uint8_t sat, uint8_t val
) {
    _matrix->led(x, y).setHSV(hue, sat, val);
}
