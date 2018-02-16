#include "Pulse.hpp"

Pulse::Pulse(
    double amplitude, double phase,
    double frequency, double min, double max
) {
    // the amplitude is the overall brightness that is set
    // once to balance the overall brightness of different coloured LEDs
    setAmplitude(amplitude);
    // the phase will also typically be set once to either keep all LEDs
    // in sync or pulsing in sequence
    setPhase(phase);
    // the remaining three arguments are likely to change within the
    // lifetime of the object, e.g. when switching from a slow pulse
    // to a fast flash...
    setFrequencyRange(frequency, min, max);
}

void Pulse::setAmplitude(double amplitude) {
    _amplitude = amplitude;
}

void Pulse::setPhase(double phase) {
    _phase = phase;
}

void Pulse::setFrequencyRange(
    double frequency, double min, double max
) {
    setFrequency(frequency);
    setRange(min, max);
}

void Pulse::setFrequency(
    double frequency
) {
    _frequency = frequency;
}

void Pulse::setRange(
    double min, double max
) {
    _min = min;
    _max = max;
    _range = _max - _min;
}

void Pulse::off() {
    setFrequencyRange(1, 0, 0);
}

void Pulse::throb() {
    setFrequencyRange(ThrobFreq, ThrobMin, ThrobMax);
}

void Pulse::flash() {
    setFrequencyRange(FlashFreq, FlashMin, FlashMax);
}

double Pulse::pulse(double time) {
    double phi;
    // phi is the angle of rotation
    phi = _phase + _frequency * time;
    // sin of phi radians returns -1 to +1 which we normalise to the range 0 to 1
    phi = sin(phi * 2 * M_PI) / 2 + 0.5;
    // then we scale it to the range from min to max and
    // multiply by the overall amplitude
    return _amplitude * (_min  + _range * phi);
}
