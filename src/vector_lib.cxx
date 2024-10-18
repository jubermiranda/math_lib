#include "vector_lib.h"
#include <cmath>

Vector::Vector() : p(Point(0, 0, 0)) {}

Vector::Vector(Point p) : p(p) {}

Vector::Vector(Point a, Point b) : p(b - a) {}

Vector::Vector(float x, float y, float z) : p(Point(x, y, z)) {}

float Vector::mod() const {
  float result = std::sqrt(mod_square());
  return result;
}

float Vector::mod_square() const{
  return (p.x * p.x + p.y * p.y + p.z * p.z);
}

bool Vector::is_null() const {
  bool result = p.x == 0 && p.y == 0 && p.z == 0;
  return result;
}

bool Vector::operator==(const Vector& other) const{
  return (this->p == other.p);
}


/* VectorRelation: TODO
static bool is_parallel(const Vector &, const Vector &);
static bool is_ortogonal(const Vector &, const Vector &);
static bool is_opposite(const Vector &, const Vector &);
static bool is_collinear(const Vector &, const Vector &);
static bool is_coplanar(const Vector &, const Vector &);
*/
