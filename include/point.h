#pragma once

#include <array>
#include <cstddef>

template <size_t DIM> class Point {
public:
  std::array<double, DIM> coords;

  template <typename... Args>
  Point(Args... args) : coords{static_cast<double>(args)...} {
    static_assert(sizeof...(args) == DIM, "Invalid number of arguments");
  }
  Point(const Point<DIM> &);
  Point();

  size_t size() { return coords.size(); }

  double &operator[](size_t i);
  const double operator[](size_t i) const;

  Point<DIM> &operator=(const Point<DIM> &);
  Point<DIM> operator-(const Point<DIM> &) const;
  Point<DIM> operator+(const Point<DIM> &) const;
  Point<DIM> operator*(double scalar) const;
  bool operator==(const Point<DIM> &) const;
  bool operator!=(const Point<DIM> &) const;
};

#include "point.tpp"

