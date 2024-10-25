#include "vector_lib.h"
#include <cmath>
#include <stdexcept>

Vector::Vector() : p(Point(0, 0, 0)) {}

Vector::Vector(Point p) : p(p) {}

Vector::Vector(Point a, Point b) : p(b - a) {}

Vector::Vector(float x, float y, float z) : p(Point(x, y, z)) {}

float Vector::mod() const {
  float result = std::sqrt(mod_square());
  return result;
}

float Vector::mod_square() const { return (p.x * p.x + p.y * p.y + p.z * p.z); }

bool Vector::is_null() const {
  bool result = p.x == 0 && p.y == 0 && p.z == 0;
  return result;
}

bool Vector::is_unit() const {
  return (mod() == 1);
}

bool Vector::operator==(const Vector &other) const {
  return (this->p == other.p);
}

bool Vector::operator!=(const Vector &other) const {
  return !(this->p == other.p);
}

Vector Vector::unit() const {
  Point p_result(p.x / mod(), p.y / mod(), p.z / mod());
  Vector unit_vec(p_result);

  return unit_vec;
}

Vector Vector::scale(float factor) const {
  return Vector(p.x * factor, p.y * factor, p.z * factor);
}

Vector Vector::direction_cossines() const {
  float mod = this->mod();
  float coss_x = p.x / mod;
  float coss_y = p.y / mod;
  float coss_z = p.z / mod;

  return Vector(coss_x, coss_y, coss_z);
}

Vector Vector::opposite() const { return Vector(p.x * -1, p.y * -1, p.z * -1); }

Vector Vector::operator+(const Vector &other) const {
  return Vector(p.x + other.x(), p.y + other.y(), p.z + other.z());
}

/* VectorRelation: TODO
static bool is_parallel(const Vector &, const Vector &);
static bool is_ortogonal(const Vector &, const Vector &);
static bool is_opposite(const Vector &, const Vector &);
static bool is_collinear(const Vector &, const Vector &);
static bool is_coplanar(const Vector &, const Vector &);
*/
