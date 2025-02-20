#ifndef VECTOR_LIB_H_
#define VECTOR_LIB_H_

#include "point.h"
#include <cstddef>

enum class VectorRelation { PARALLEL, ORTHOGONAL, COLLINEAR, NONE };

template <size_t DIM> class Vector {
public:
  Vector();
  Vector(Point p);
  Vector(Point a, Point b);

  double mod() const;
  double mod_square() const;

  Vector<DIM> unit() const;
  Vector<DIM> scale(double factor) const;
  Vector<DIM> direction_cossines() const;
  Vector<DIM> opposite() const;
  Vector<DIM> rotate_around(double angle, size_t d) const;

  bool is_unit() const;
  bool is_null() const;

  Vector<DIM> operator+(const Vector<DIM> &) const;
  Vector<DIM> operator-(const Vector<DIM> &) const;
  double operator*(const Vector<DIM> &) const;
  bool operator==(const Vector<DIM> &) const;
  bool operator!=(const Vector<DIM> &) const;

  static double angle(const Vector<DIM> &, const Vector<DIM> &);
  static Vector<DIM> cross_product(const Vector<DIM> &, const Vector<DIM> &);
  static Vector<DIM> projection(const Vector<DIM> &, const Vector<DIM> &);

private:
  Point<DIM> p;
};

Vector<DIM> operator*(double, const Vector<DIM> &);
Vector<DIM> operator*(const Vector<DIM> &, double);

#endif
