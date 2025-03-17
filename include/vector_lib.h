#ifndef VECTOR_LIB_H_
#define VECTOR_LIB_H_

#include "point.h"
#include <cstddef>

enum class VectorRelation { PARALLEL, ORTHOGONAL, COLLINEAR, NONE };

template <size_t DIM> class Vector {
public:
  Vector();
  Vector(const Point<DIM> &);
  Vector(const Point<DIM> &, const Point<DIM> &);
  template <typename... Args> Vector(Args... args);

  double mod() const;
  double mod_square() const;
  double coord(size_t) const;

  Vector<DIM> unit() const;
  Vector<DIM> scale(double factor) const;
  Vector<DIM> direction_cossines() const;
  Vector<DIM> opposite() const;
  Vector<DIM> rotate_around(double angle, size_t d) const;

  bool is_unit() const;
  bool is_null() const;

  Vector<DIM> operator+(const Vector<DIM> &) const;
  Vector<DIM> operator-(const Vector<DIM> &) const;
  Vector<DIM> operator*(double) const;
  Vector<DIM> operator/(double) const;
  double operator*(const Vector<DIM> &) const; // <- scalar product
  bool operator==(const Vector<DIM> &) const;
  bool operator!=(const Vector<DIM> &) const;

  static double angle(const Vector<DIM> &, const Vector<DIM> &);
  static Vector<DIM> cross_product(const Vector<DIM> &, const Vector<DIM> &);
  static Vector<DIM> projection(const Vector<DIM> &, const Vector<DIM> &);

private:
  Point<DIM> p;
};

template <size_t DIM> Vector<DIM> operator*(const double, const Vector<DIM> &);

#include "vector_lib.tpp"

#endif
