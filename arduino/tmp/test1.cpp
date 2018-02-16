#include "LEDMatrix.hpp"
#include "Cursor.hpp"
#include "TrailBlazer.hpp"
#include "Pulse.hpp"
#include "Button.hpp"
#include <unistd.h>

void test_pulse();
void test_button();
void debug_button_pulse(Button *b);

int main() {
    test_button();
}

void hello(Button *b) {
    printf("Button %d/%d was pressed\n", b->swpin(), b->ledpin());
}

void goodbye(Button *b) {
    printf("Button %d/%d was released\n", b->swpin(), b->ledpin());
}

void test_button() {
    Button b1(1,2);
    Button b2(3,4);

    b1.deactivate();
    printf("Button 1 is %s\n", b1.active() ? "active" : "inactive");
    debug_button_pulse(&b1);

    b1.activate();
    printf("Button 1 is %s\n", b1.active() ? "active" : "inactive");
    debug_button_pulse(&b1);

    printf("Binding handlers\n");
    b1.onPress(hello);
    b1.onRelease(goodbye);

    b1.pressed();
    debug_button_pulse(&b1);

    b1.released();
    debug_button_pulse(&b1);
}

void debug_button_pulse(Button *b) {
    for (double time = 0.0; time < 3; time += 0.05) {
        b->pulse(time);
    }
}

void test_pulse() {
    Pulse p(1,0.75);
    for (double time = 0.0; time < 2; time += 0.01) {
        printf("pulse at time %lf: %lf\n", time, p.pulse(time));
    }
}

void test_cursor() {
    LEDMatrix matrix(24,18, BottomRight, RowsSnake);
    Cursor cursor(
        &matrix,
        2, 2,               // origin
        24, 10,               // velocity
        Reflect, Reflect,   // edge handling
        //Wrap, Wrap,   // edge handling
        12                   // trail length
    );
    TrailBlazer blazer;

    //for (double time = 0.0; time < 5.0; time += 1.0) {
    //    cursor.move(time);
    //}

    for (double time = 0.0; time < 1000.0; time += 0.01) {
        if (cursor.move(time)) {
            cursor.debugMatrix();
            cursor.blaze(&blazer);
        }
        usleep(10000);
    }
}

void test_matrix() {
    LEDMatrix matrix1(12, 6, TopLeft, RowsZigZag);
    LEDMatrix matrix2(12, 6, TopRight, RowsZigZag);
    LEDMatrix matrix3(12, 6, BottomLeft, RowsZigZag);
    LEDMatrix matrix4(12, 6, BottomRight, RowsZigZag);

    LEDMatrix matrix5(12, 6, TopLeft, RowsSnake);
    LEDMatrix matrix6(12, 6, TopRight, RowsSnake);
    LEDMatrix matrix7(12, 6, BottomLeft, RowsSnake);
    LEDMatrix matrix8(12, 6, BottomRight, RowsSnake);

    //LEDMatrix matrix(24, 18, BottomRight, RowsSnake);
    Cursor cursor(&matrix5, 0, 0, 3, 0.1);

}
