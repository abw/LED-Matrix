#include "LEDMatrix.hpp"

LEDMatrix::LEDMatrix(
    CRGB *fastleds,
    unsigned int width, unsigned int height,
    LEDMatrixOrigin origin,
    LEDMatrixOrient orient
) {
    _width  = width;
    _height = height;
    _size   = width * height;
    _origin = origin;
    _orient = orient;
    _leds   = new uint16_t[_size];
    _fastleds = fastleds;
    printf("Created LED matrix: %dx%d\n", _width, _height);
    init();
}


void LEDMatrix::init() {
    unsigned int maxx = _width  - 1;
    unsigned int maxy = _height - 1;
    bool bottom = _origin == BottomLeft || _origin == BottomRight;
    bool right  = _origin == TopRight   || _origin == BottomRight;
    bool top    = ! bottom;
    bool left   = ! right;
    bool cols   = _orient == ColsSnake || _orient == ColsZigZag;
    bool snake  = _orient == ColsSnake || _orient == RowsSnake;
    bool rows   = ! cols;
    bool zigzag = ! snake;
    int xorigin = right  ? _width  - 1 : 0;
    int yorigin = top    ? _height - 1 : 0;
    int dx      = right  ? (rows ? -1 : -_height) : (rows ? 1 : _height);
    int dy      = top    ? (cols ? -1 : -_width ) : (cols ? 1 : _width);
    int x, y;

    printf(
        "origin:%d bottom:%d top:%d left:%d right:%d\n",
        _origin, bottom, top, left, right
    );
    printf(
        "orient:%d rows:%d cols:%d snake:%d zigzag:%d\n",
        _orient, rows, cols, snake, zigzag
    );
    printf(
        "xorigin:%d yorigin:%d dx:%d dy:%d\n",
        xorigin, yorigin, dx, dy
    );

    // populate the mapping table from (x,y) to LED no
    for (y = 0; y < _height; y++) {
        for (x = 0; x < _width; x++) {
            int xdiff = x - xorigin;
            int ydiff = y - yorigin;
            unsigned int ledno = (xdiff * dx) + (ydiff * dy);
            //printf("%d,%d => %d\n", x, y, ledno);
            _leds[y * _width + x] = ledno;
        }
    }
    // rearrange to account for rows/cols that snake back and forth
    if (snake) {
        if (rows) {
            // reverse every other row
            for (int y = 1; y < _height; y += 2) {
                int yy   = top ? maxy - y : y;
                int base = yy * _width;
                for (int x = 0; x < _width / 2; x++) {
                    int z   = maxx - x;
                    int tmp = _leds[base + x];
                    _leds[base + x] = _leds[base + z];
                    _leds[base + z] = tmp;
                }
            }
        }
        else {
            // reverse every other column
            for (int x = 1; x < _width; x += 2) {
                int xx = right ? maxx - x : x;
                for (int y = 0; y < _height / 2; y++) {
                    int yy  = maxy - y;
                    int tmp = _leds[y * _width + xx];
                    _leds[y * _width + xx] = _leds[yy * _width + xx];
                    _leds[yy * _width + xx] = tmp;
                }
            }
        }
    }

    debug();
}

void LEDMatrix::debug() {
    // dump table for debugging
    // NOTE: we do this in reverse order because the origin is at the
    // bottom
    for (int y = _height - 1; y >= 0; y--) {
        for (int x = 0; x < _width; x++) {
            printf("%3d ", _leds[y * _width + x]);
        }
        printf("\n");
    }
}

unsigned int LEDMatrix::width() {
    return _width;
}

unsigned int LEDMatrix::height() {
    return _height;
}

CRGB *LEDMatrix::led(unsigned int x, unsigned int y) {
    return &_fastleds[
        _leds[y * _width + x]
    ];
}

void LEDMatrix::screenRGB(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < _size; i++) {
        _fastleds[i].setRGB(red, green, blue);
    }
}

LEDMatrix::~LEDMatrix() {
    delete [] _leds;
    printf("Destroyed LED matrix: %dx%d\n", _width, _height);
}
