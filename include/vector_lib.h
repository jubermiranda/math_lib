#ifndef VECTOR_LIB_H_
#define VECTOR_LIB_H_

#include "point.h"

enum class VectorRelation { PARALLEL, ORTHOGONAL, COLLINEAR, NONE };

class Vector {
public:
  Vector();
  Vector(Point p);
  Vector(Point a, Point b);
  Vector(double x, double y, double z);

  double x() const { return p.x; };
  double y() const { return p.y; };
  double z() const { return p.z; };
  double mod() const;
  double mod_square() const;

  Vector unit() const;
  Vector scale(double factor) const;
  Vector direction_cossines() const;
  Vector opposite() const;
  Vector rotate_around_x(double angle) const;
  Vector rotate_around_y(double angle) const;
  Vector rotate_around_z(double angle) const;
  Vector reflect_across_plane(const Vector &normal) const;

  bool is_unit() const;
  bool is_null() const;

  Vector operator+(const Vector &) const;
  Vector operator-(const Vector &) const;
  Vector operator*(double) const;
  double operator*(const Vector &) const;
  Vector operator/(double) const;
  bool operator==(const Vector &) const;
  bool operator!=(const Vector &) const;

  static double angle(const Vector &, const Vector &);
  static double mix_product(const Vector &, const Vector &, const Vector &);
  static Vector cross_product(const Vector &, const Vector &);
  static Vector projection(const Vector &, const Vector &);

private:
  Point p;
};

#endif
