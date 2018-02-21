#include "LEDMatrix.hpp"

#define DEBUG_MATRIX 0

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
#if DEBUG_MATRIX
    printf("Created LED matrix: %dx%d\n", _width, _height);
#endif
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

#if DEBUG_MATRIX
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
#endif

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

#if DEBUG_MATRIX
    debug();
#endif
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

unsigned int LEDMatrix::x(double fx, LEDMatrixBounds bounds) {
    long ix = floor(fx < 0 ? fx - epsilon : fx + epsilon);
    long lx = ix % _width;
    unsigned long ledx = fx < 0 ? _width  - 1 + lx : lx;

    if (bounds == Reflect) {
        int rx = ix < 0 ? abs(ix) / _width + 1 : ix / _width;
        if (rx % 2) {
            ledx = _width - 1 - ledx;
        }
    }
    return ledx;
}

unsigned int LEDMatrix::y(double fy, LEDMatrixBounds bounds) {
    long iy = floor(fy < 0 ? fy - epsilon : fy + epsilon);
    long ly = iy % _height;
    unsigned long ledy = fy < 0 ? _height - 1 + ly : ly;

    if (bounds == Reflect) {
        int ry = iy < 0 ? (abs(iy) / _height + 1) : iy / _height;
        if (ry % 2) {
            ledy = _height - 1 - ledy;
        }
    }
    return ledy;
}

Point LEDMatrix::xy(
    double fx, double fy, LEDMatrixBounds xbounds, LEDMatrixBounds ybounds
) {
    Point p;
    p.x = x(fx, xbounds);
    p.y = y(fy, ybounds);
    return p;
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
#if DEBUG_MATRIX
    printf("Destroyed LED matrix: %dx%d\n", _width, _height);
#endif
}
