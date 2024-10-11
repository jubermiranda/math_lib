#ifndef VECTOR_LIB_H_
#define VECTOR_LIB_H_

#include "point.h"

class Vector {
public:
  Vector(Point p);
  Vector(Point a, Point b);

  float mod() const;
  float cos_x() const;
  float cos_y() const;
  float cos_z() const;

  Point middle_point() const;
  Vector product(const Vector &) const;
  Vector opposite() const;
  Vector unit() const;
  Vector projection(const Vector &) const;

  bool operator==(const Vector &) const;
  Vector operator+(const Vector &) const;
  Vector operator-(const Vector &) const;
  Vector operator*(float) const;
  float operator*(const Vector &) const;

  static bool is_parallel(const Vector &, const Vector &);
  static bool is_ortogonal(const Vector &, const Vector &);
  static bool is_opposite(const Vector &, const Vector &);
  static bool is_collinear(const Vector &, const Vector &);
  static bool is_coplanar(const Vector &, const Vector &);
  static float angle(const Vector &, const Vector &);

  static float distance(const Point& a, const Point& b);

private:
  Point p;
};

#endif
