//---------------------------------------------------------------------
// Button.hpp
//
// Button class for monitoring switch and updating LED bezel
//
// Written by Andy Wardley <abw@wardley.org> February 2018
//---------------------------------------------------------------------

#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <inttypes.h>
#include <stdio.h>
#include "Pulse.hpp"
#include "Arduino.h"
#include "Bounce2.h"

const unsigned long DebounceInterval = 25;  // milliseconds

class Button;
typedef void (* ButtonHandler)(Button *button);

class Button {
public:
    Button(
        unsigned int swpin,
        unsigned int ledpin,
        double brightness=1.0,
        double phase=0.0,
        bool active=true,
        ButtonHandler onPress=NULL,
        ButtonHandler onRelease=NULL
    );
    bool active();
    void activate();
    void deactivate();
    void setHandlers(
        ButtonHandler press=NULL,
        ButtonHandler release=NULL
    );
    void onPress(ButtonHandler press);
    void onRelease(ButtonHandler release);
    void clearHandlers();
    bool check();
    void pulse(double time);
    void pressed();
    void released();
    unsigned int swpin();
    unsigned int ledpin();

private:
    unsigned int _swpin;
    unsigned int _ledpin;
    bool _active;
    Bounce _debouncer;
    ButtonHandler _onPress;
    ButtonHandler _onRelease;
    Pulse _pulse;
};

#endif
