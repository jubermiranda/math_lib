#ifndef POINT_LIB_TPP_
#define POINT_LIB_TPP_

#include <cstddef>

template <size_t DIM>
Point<DIM>::Point(const Point<DIM> &other) : coords(other.coords) {}

template <size_t DIM>
Point<DIM>::Point(){
  for(size_t i=0; i < DIM; i++)
    coords[i] = 0.0;
}

template <size_t DIM> double &Point<DIM>::operator[](size_t i) {
  return this->coords.at(i);
}

template <size_t DIM> const double Point<DIM>::operator[](size_t i) const {
  return this->coords.at(i);
}

template <size_t DIM>
Point<DIM> Point<DIM>::operator+(const Point<DIM> &other) const {
  Point<DIM> result = Point<DIM>();
  for (size_t i = 0; i < DIM; i++)
    result[i] = this->operator[](i) + other[i];
  return result;
}

template <size_t DIM>
Point<DIM> Point<DIM>::operator-(const Point<DIM> &other) const {
  Point<DIM> result = Point<DIM>();
  for (size_t i = 0; i < DIM; i++)
    result[i] = this->operator[](i) - other[i];
  return result;
}

template <size_t DIM> Point<DIM> Point<DIM>::operator*(double scalar) const {
  Point<DIM> result = Point<DIM>();
  for (size_t i = 0; i < DIM; i++)
    result[i] = this->operator[](i) * scalar;
  return result;
}

template <size_t DIM>
Point<DIM> &Point<DIM>::operator=(const Point<DIM> &other) {
  if (this != &other)
    this->coords = other.coords;

  return *this;
}

template <size_t DIM>
bool Point<DIM>::operator==(const Point<DIM> &other) const {
  for (size_t i = 0; i < DIM; i++)
    if (this->operator[](i) != other[i])
      return false;
  return true;
}

template <size_t DIM>
bool Point<DIM>::operator!=(const Point<DIM> &other) const {
  return !(this->operator==(other));
}

#endif /* ifndef POINT_LIB_TPP_ */
