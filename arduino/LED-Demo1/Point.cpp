#include "Point.hpp"

Point::Point(
    unsigned int xx, unsigned int yy
) {
    x = xx;
    y = yy;
}

bool Point::operator==(const Point& other) {
  return x == other.x && y == other.y;
}
