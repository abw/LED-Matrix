#include "Point.hpp"

void setPoint(
    Point *p,
    unsigned int x, unsigned int y
) {
    p->x = x;
    p->y = y;
}

bool eqPoint(
    Point *a,
    Point *b
) {
    return a->x == b->x
        && a->y == b->y;
}
