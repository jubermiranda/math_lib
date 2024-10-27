#include "point.h"

Point Point::operator+(const Point &other) const {
  return Point(this->x + other.x, this->y + other.y, this->z + other.z);
}

Point Point::operator-(const Point &other) const {
  return Point(this->x - other.x, this->y - other.y, this->z - other.z);
}

Point Point::operator*(double scalar) const {
  return Point(this->x * scalar, this->y * scalar, this->z * scalar);
}

Point &Point::operator=(const Point &other) {
  x = other.x;
  y = other.y;
  z = other.z;

  return *this;
}

bool Point::operator==(const Point &other) const {
  return (x == other.x && y == other.y && z == other.z);
}

bool Point::operator!=(const Point &other) const {
  return !(operator==(other));
}
