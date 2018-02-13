#include "LEDMatrix.hpp"
#include "Cursor.hpp"

int main() {
    LEDMatrix matrix(12,6);
    Cursor cursor(
        &matrix,
        0, 0,               // origin
        6, 2,               // velocity
        Reflect, Reflect,   // edge handling
        5                   // trail length
    );

    for (double time = 0.0; time < 10.0; time += 0.1) {
        cursor.move(time);
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
