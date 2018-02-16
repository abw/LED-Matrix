#include "Cursor.hpp"

#define DEBUG_TRAIL 0

Cursor::Cursor(
    LEDMatrix *matrix,
    long xorg, long yorg, double dx, double dy,
    CursorFold foldX, CursorFold foldY,
    unsigned int trail
) {
    _matrix   = matrix;
    _xorg     = xorg;
    _yorg     = yorg;
    _dx       = dx;
    _dy       = dy;
    _reflectX = (foldX == Reflect);
    _reflectY = (foldY == Reflect);
    _width    = matrix->width();
    _height   = matrix->height();
    _trail    = trail;
    _size     = trail + 1;
    _length   = 1;
    _head     = 0;
    _points   = new Point[_size];
    _points[_head].x = _xorg;
    _points[_head].y = _yorg;
    debug();
}

void Cursor::debug() {
    printf(
        "Cursor origin at %ld,%ld with velocity vector %lf,%lf\n",
        _xorg, _yorg, _dx, _dy
    );
}

Cursor::~Cursor() {
    _points   = new Point[_trail + 1];
    delete [] _points;
    printf("Destroyed cursor points\n");
}

void Cursor::start(double time) {
    _start = _time = time;
}

bool Cursor::move(double time) {
    double dt = time - _start;
    double fx = _xorg + _dx * dt;
    double fy = _yorg + _dy * dt;
    long   ix = floor(fx < 0 ? fx - epsilon : fx + epsilon);
    long   iy = floor(fy < 0 ? fy - epsilon : fy + epsilon);
    long   lx = ix % _width;
    long   ly = iy % _height;
    unsigned long ledx = fx < 0 ? _width  - 1 + lx : lx;
    unsigned long ledy = fy < 0 ? _height - 1 + ly : ly;
    _time = time;

    if (_reflectX) {
        int rx = ix < 0 ? abs(ix) / _width + 1 : ix / _width;
        if (rx % 2) {
            ledx = _width - 1 - ledx;
        }
    }
    if (_reflectY) {
        int ry = iy < 0 ? (abs(iy) / _height + 1) : iy / _height;
        if (ry % 2) {
            ledy = _height - 1 - ledy;
        }
    }
    if (_points[_head].x == ledx && _points[_head].y == ledy) {
        return false;
    }

#if DEBUG_TRAIL
    printf(
        "At time %lf cursor at %lf,%lf (%ld,%ld) mapped to (%ld,%ld) %ld,%ld\n",
        time, fx, fy, ix, iy, lx, ly, ledx, ledy
    );
    printf(
        "ix:%ld abs(ix)/width:%ld abs(ix)/width%%2:%ld\n",
        ix, abs(ix) / _width, abs(ix) / _width % 2
    );
#endif

    _head = (_head + 1) % _size;
    _points[_head].x = ledx;
    _points[_head].y = ledy;

    if (_length < _size) {
        _length++;
    }

    //debugMatrix();

#if DEBUG_TRAIL
    printf("trail:");
    for (unsigned i = 0; i < _length; i++) {
        Point *p = &_points[(_head + _size - i) % _size];
        printf(" %d:(%d,%d)", i, p->x, p->y);
    }
    printf("\n");
#endif

    return true;
}

void Cursor::changeDirection(double dx, double dy) {
    // If we just change the dx and dy then we'll get a discontinuity
    // as the cursor jumps from it's old position to the new one.
    // So instead we reset the _xorg, _yorg and _start time so the
    // new cursor originates from the current position at the current
    // time
    _xorg  = _points[_head].x;
    _yorg  = _points[_head].y;
    _dx    = dx;
    _dy    = dy;
    _start = _time;
}

void Cursor::blaze(TrailBlazer *tb) {
    // blaze the trail in reverse order from tail to head
    // if the trail crosses itself then the head should dominate
    for (int i = _length - 1; i >= 0; i--) {
        Point *p = &_points[(_head + _size - i) % _size];
        tb->blaze(i, _length, p->x, _width, p->y, _height, _time);
    }
}

void Cursor::debugMatrix() {
    //char *snake = "@Xx=-";
    const char *snake = "@XYZ#xyz#=-=-,..";
    for (int y = _height - 1; y >= 0; y--) {
        for (int x = 0; x < _width; x++) {
            int printed = 0;
            for (int i = 0; i < strlen(snake); i++) {
                if (_length > i) {
                    Point *p = &_points[(_head + _size - i) % _size];
                    if (x == p->x && y == p->y) {
                        printf("%c", snake[i]);
                        printed++;
                        break;
                    }
                }
            }
            if (! printed) {
                int vert = (x == 0 || x == _width - 1);
                int horz = (y == 0 || y == _height - 1);
                if (vert && horz) {
                    printf("+");
                }
                else if (vert) {
                    printf("|");
                }
                else if (horz) {
                    printf("-");
                }
                else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}
