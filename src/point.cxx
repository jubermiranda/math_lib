#include "point.h"

Point Point::operator+(const Point &other) const{
  Point result(this->x + other.x, this->y + other.y, this->z + other.z);
  return result;
}

Point Point::operator-(const Point &other) const {
  Point result(this->x - other.x, this->y - other.y, this->z - other.z);
  return result;
}

bool Point::operator==(const Point& other) const{
  return (x == other.x && y == other.y && z == other.z);
}
bool Point::operator==(const Point&& other) const{
  return (x == other.x && y == other.y && z == other.z);
}
