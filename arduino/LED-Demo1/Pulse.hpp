//---------------------------------------------------------------------
// Pulse.hpp
//
// Waveform generator for pulsing LEDs on button bezels
//
// Written by Andy Wardley <abw@wardley.org> February 2018
//---------------------------------------------------------------------

#ifndef PULSE_HPP
#define PULSE_HPP
#include <math.h>

// settings for two standard modes: slow throb and fast flash
const double ThrobFreq = 0.25;
const double ThrobMin  = 0.02;
const double ThrobMax  = 0.8;

const double FlashFreq = 8.0;
const double FlashMin  = 0.0;
const double FlashMax  = 1.0;


class Pulse {
public:
    Pulse(
        double amplitude=1, double phase=0,
        double frequency=1, double min=0, double max=1
    );
    void setAmplitude(double amplitude);
    void setPhase(double phase);
    void setFrequencyRange(double frequency=1, double min=0, double max=1);
    void setFrequency(double frequency);
    void setRange(double min, double max);
    void off();
    void throb();
    void flash();
    double pulse(double time);
private:
    double _amplitude;
    double _phase;
    double _frequency;
    double _min;
    double _max;
    double _range;
};

#endif
