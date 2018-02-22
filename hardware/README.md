# LED-Matrix Hardware
This directory contains the Eagle schematics, board designs and Gerber
files for the LED Matrix.

The [Power Board](Power%20Board/v1.2) is a power distribution module
that hosts 3 MP1584EN buck regulator modules.  These provide power for
the LED strips.

The [Control Board](Control%20Board/v1.0) is a board which can be used
as an all-in-one Arduino shield, or as a pair of mother/daughter boards.
It provides a connection to the Power Board to receive power and return
data for the LED strips.  It also has 4 connectors for push-button
switches with integrated LEDs in the bezel.
