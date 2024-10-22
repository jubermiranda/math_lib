#ifndef VECTOR_LIB_H_
#define VECTOR_LIB_H_

#include "point.h"

enum class VectorRelation { PARALLEL, ORTHOGONAL, COLLINEAR, NONE };

class Vector {
public:
  Vector();
  Vector(Point p);
  Vector(Point a, Point b);
  Vector(float x, float y, float z);

  float x() const { return p.x; };
  float y() const { return p.y; };
  float z() const { return p.z; };
  float mod() const;
  float mod_square() const;

  Vector unit() const;
  Vector scale(float factor) const;
  Vector direction_cossines() const;
  Vector opposite() const;
  Vector rotate_around_x(float angle) const;
  Vector rotate_around_y(float angle) const;
  Vector rotate_around_z(float angle) const;
  Vector reflect_across_plane(const Vector &normal) const;

  bool is_unit() const;
  bool is_null() const;

  Vector operator+(const Vector &) const;
  Vector operator-(const Vector &) const;
  Vector operator*(float) const;
  float operator*(const Vector &) const;
  bool operator==(const Vector &) const;
  bool operator==(const Vector &&) const;

  static float angle(const Vector &, const Vector &);
  static float mix_product(const Vector &, const Vector &, const Vector &);
  static Vector cross_product(const Vector &, const Vector &);
  static Vector projection(const Vector &, const Vector &);

private:
  Point p;
};

#endif
