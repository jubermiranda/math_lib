#include "vector_lib.h"
#include <cmath>
#include <numbers>
#include <stdexcept>

using std::cos;
using std::sin;

Vector::Vector() : p(Point(0, 0, 0)) {}

Vector::Vector(Point p) : p(p) {}

Vector::Vector(Point a, Point b) : p(b - a) {}

Vector::Vector(double x, double y, double z) : p(Point(x, y, z)) {}

double Vector::mod() const {
  double result = std::sqrt(mod_square());
  return result;
}

double Vector::mod_square() const {
  return (p.x * p.x + p.y * p.y + p.z * p.z);
}

bool Vector::is_null() const {
  bool result = p.x == 0 && p.y == 0 && p.z == 0;
  return result;
}

bool Vector::is_unit() const { return (mod() == 1); }

Vector Vector::unit() const {
  Point p_result(p.x / mod(), p.y / mod(), p.z / mod());
  Vector unit_vec(p_result);

  return unit_vec;
}

Vector Vector::scale(double factor) const {
  return Vector(p.x * factor, p.y * factor, p.z * factor);
}

Vector Vector::direction_cossines() const {
  double mod = this->mod();
  double coss_x = p.x / mod;
  double coss_y = p.y / mod;
  double coss_z = p.z / mod;

  return Vector(coss_x, coss_y, coss_z);
}

Vector Vector::opposite() const { return Vector(p.x * -1, p.y * -1, p.z * -1); }

Vector Vector::rotate_around_x(double angle) const {
  long double pi = std::numbers::pi_v<long double>;
  long double radians = angle * pi / 180.0;

  long double new_y = (p.y * cos(radians)) + (p.z * -sin(radians));
  long double new_z = (p.y * sin(radians)) + (p.z * cos(radians));

  return Vector(p.x, new_y, new_z);
}

Vector Vector::rotate_around_y(double angle) const {
  long double pi = std::numbers::pi_v<long double>;
  long double radians = angle * pi / 180.0;

  long double new_x = (p.x * cos(radians)) + (p.z * sin(radians));
  long double new_z = (p.x * -sin(radians)) + (p.z * cos(radians));

  return Vector(new_x, p.y, new_z);
}

Vector Vector::rotate_around_z(double angle) const {
  long double pi = std::numbers::pi_v<long double>;
  long double radians = angle * pi / 180.0;

  long double new_x = (p.x * cos(radians)) + (p.y * -sin(radians));
  long double new_y = (p.x * sin(radians)) + (p.y * cos(radians));

  return Vector(new_x, new_y, p.z);
}

Vector Vector::operator+(const Vector &other) const {
  return Vector(p.x + other.x(), p.y + other.y(), p.z + other.z());
}

Vector Vector::operator-(const Vector &other) const {
  return Vector(p.x - other.x(), p.y - other.y(), p.z - other.z());
}

Vector Vector::operator/(double n) const {
  return Vector(p.x / n, p.y / n, p.z / n);
}

bool Vector::operator==(const Vector &other) const {
  return (this->p == other.p);
}

bool Vector::operator!=(const Vector &other) const {
  return !(this->p == other.p);
}

double Vector::operator*(const Vector& other) const{
  double result = 
    x() * other.x()
    + y() * other.y()
    + z() * other.z();
  return result;
}

Vector Vector::operator*(double k) const {
  return (Vector(this->p * k));
}


Vector operator*(double k, const Vector& v){
  return v * k;
}

// static

double Vector::angle(const Vector& v1, const Vector& v2){
  return 0;
}

/* VectorRelation: TODO
static bool is_parallel(const Vector &, const Vector &);
static bool is_ortogonal(const Vector &, const Vector &);
static bool is_opposite(const Vector &, const Vector &);
static bool is_collinear(const Vector &, const Vector &);
static bool is_coplanar(const Vector &, const Vector &);
*/
