#include "point.h"

Point Point::operator+(const Point &other) {
  Point result(this->x + other.x, this->y + other.y, this->z + other.z);
  return result;
}

Point Point::operator-(const Point &other) {
  Point result(this->x - other.x, this->y - other.y, this->z - other.z);
  return result;
}
