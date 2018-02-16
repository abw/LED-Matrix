#include "Waveforms.hpp"
#include <math.h>

#define PI2 M_PI*2

double sinWave(double theta) {
    return (sin(theta * PI2) + 1) / 2;
}

double squareWave(double theta) {
    return fmod(theta, 1) < 0.5 ? 1 : 0;
}

double rampUpWave(double theta) {
    return fmod(theta, 1);
}

double rampDownWave(double theta) {
    return 1 - fmod(theta, 1);
}
