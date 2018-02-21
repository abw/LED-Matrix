#include "Button.hpp"

Button::Button(
    unsigned int swpin,
    unsigned int ledpin,
    double brightness,
    double phase,
    bool active,
    ButtonHandler onPress,
    ButtonHandler onRelease
) {
    _swpin = swpin;
    _ledpin = ledpin;
    _onPress = onPress;
    _onRelease = onRelease;
    _debouncer = Bounce();
    _debouncer.attach(_swpin);
    _debouncer.interval(DebounceInterval);
    _pulse.setAmplitude(brightness);
    _pulse.setPhase(phase);
    pinMode(_swpin, INPUT);
    pinMode(_ledpin, OUTPUT);
    if (active) {
        activate();
    }
    else {
        deactivate();
    }
}

bool Button::active() {
    return _active;
}

void Button::activate() {
    _active = true;
    _pulse.throb();
}

void Button::deactivate() {
    _active = false;
    _pulse.off();
    analogWrite(_ledpin, 0);
}

unsigned int Button::swpin() {
    return _swpin;
}

unsigned int Button::ledpin() {
    return _ledpin;
}

void Button::setHandlers(
    ButtonHandler press,
    ButtonHandler release
) {
    onPress(press);
    onRelease(release);
}

void Button::onPress(ButtonHandler press) {
    _onPress = press;
}

void Button::onRelease(ButtonHandler release) {
    _onRelease = release;
}

void Button::clearHandlers() {
    setHandlers(NULL, NULL);
}

bool Button::check() {
    if (_active && _debouncer.update()) {
        if (_debouncer.fell()) {
            // falling edge, i.e. button released
            released();
        }
        else {
            // must be a rising edge, i.e. button pressed
            pressed();
        }

        return true;
    }

    return false;
}

void Button::pulse(double time) {
    if (_active) {
        unsigned int val = 255 * _pulse.pulse(time);
        analogWrite(_ledpin, val);
        //printf("pulse: %d\n", val);
    }
}

void Button::pressed() {
    _pulse.flash();

    if (_onPress) {
        _onPress(this);
    }
}

void Button::released() {
    _pulse.throb();

    if (_onRelease) {
        _onRelease(this);
    }
}
