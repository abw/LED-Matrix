#include "Cursor.hpp"

Cursor::Cursor(
    LEDMatrix *matrix,
    long xorg, long yorg, double dx, double dy,
    CursorFold foldX, CursorFold foldY,
    unsigned int trail
) : _point() {
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
    if (_trail) {
        _points.reserve(_trail);
    }
    debug();
}

void Cursor::debug() {
    printf(
        "Cursor origin at %ld,%ld with velocity vector %lf,%lf\n",
        _xorg, _yorg, _dx, _dy
    );
}

Cursor::~Cursor() {
}

void Cursor::move(double time) {
    double fx = _xorg + _dx * time;
    double fy = _yorg + _dy * time;
    unsigned long ix = floor(fx + epsilon);
    unsigned long iy = floor(fy + epsilon);
    unsigned long ledx = ix % _width;
    unsigned long ledy = iy % _height;
    int reflected = 0;

    if (_reflectX && (ix / _width % 2)) {
        ledx = _width - 1 - ledx;
        reflected++;
    }
    if (_reflectY && (iy / _height % 2)) {
        ledy = _height - 1 - ledy;
        reflected++;
    }
    _point.x = ledx;
    _point.y = ledy;
    printf(
        "At time %lf cursor at %lf,%lf (%ld,%ld) mapped to %ld,%ld\n",
        time, fx, fy, ix, iy, ledx, ledy
    );

    if (_trail) {
        if (_points.size() && _points[_points.size() - 1] == _point) {
            printf("NOT pushing identical point onto list\n");
        }
        else {
            _points.push_back(_point);
            if (_points.size() > _trail) {
                printf("Popped item from trail\n");
                _points.erase(_points.begin());
            }
            printf("trail:");
            for (unsigned i=0; i<_points.size(); ++i) {
                printf(" (%d,%d)", _points[i].x, _points[i].y);
            }
            printf("\n");
        }
    }
}
