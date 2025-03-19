#include <cmath>
#include <numbers>
#include <stdexcept>
#include <type_traits>

using std::cos;
using std::sin;

template <size_t DIM> Vector<DIM>::Vector() : p(Point<DIM>()) {}

template <size_t DIM> Vector<DIM>::Vector(const Point<DIM> &p) : p(p) {}

template <size_t DIM>
Vector<DIM>::Vector(const Point<DIM> &a, const Point<DIM> &b) : p(b - a) {}

template <size_t DIM>
template <typename... Args>
Vector<DIM>::Vector(Args... args) : p(Point<DIM>(args...)) {
  static_assert(sizeof...(args) == DIM, "Invalid number of arguments");
}

template <size_t DIM> double Vector<DIM>::mod() const {
  return std::sqrt(mod_square());
}

template <size_t DIM> double Vector<DIM>::mod_square() const {
  double result = 0;
  for (size_t i = 0; i < DIM; i++)
    result += p[i] * p[i];
  return result;
}

template <size_t DIM> double Vector<DIM>::coord(size_t i) const {
  if (i > DIM)
    throw std::runtime_error("invalid index");
  return this->p[i];
}

template <size_t DIM> bool Vector<DIM>::is_null() const {
  for (size_t i = 0; i < DIM; i++)
    if (p[i] != 0)
      return false;
  return true;
}

template <size_t DIM> bool Vector<DIM>::is_unit() const { return (mod() == 1); }

template <size_t DIM> Vector<DIM> Vector<DIM>::unit() const {
  Point<DIM> p_result = p * (1.0 / this->mod());
  return Vector<DIM>(p_result);
}

template <size_t DIM> Vector<DIM> Vector<DIM>::scale(double factor) const {
  return (Vector(*this * factor));
}

template <size_t DIM> Vector<DIM> Vector<DIM>::direction_cossines() const {
  double mod = this->mod();
  Vector<DIM> result;
  for (size_t i = 0; i < DIM; i++)
    result.p[i] = this->p[i] / mod;
  return result;
}

template <size_t DIM> Vector<DIM> Vector<DIM>::opposite() const {
  Vector<DIM> result;
  for (size_t i = 0; i < DIM; i++)
    result.p[i] = (this->p[i] * -1.0);
  return result;
}

/* TODO
template <size_t DIM> Vector<DIM> Vector<DIM>::rotate_around_x(double angle)
const { long double radians = angle * M_PIl / 180.0;

  long double new_y = (p.y * cos(radians)) + (p.z * -sin(radians));
  long double new_z = (p.y * sin(radians)) + (p.z * cos(radians));

  return Vector(p.x, new_y, new_z);
}
*/

template <size_t DIM>
Vector<DIM> Vector<DIM>::operator+(const Vector<DIM> &other) const {
  Vector<DIM> result;
  for (size_t i = 0; i < DIM; i++)
    result.p[i] = this->p[i] + other.p[i];
  return result;
}

template <size_t DIM>
Vector<DIM> Vector<DIM>::operator-(const Vector<DIM> &other) const {
  Vector<DIM> result;
  for (size_t i = 0; i < DIM; i++)
    result.p[i] = this->p[i] - other.p[i];
  return result;
}

template <size_t DIM>
bool Vector<DIM>::operator==(const Vector<DIM> &other) const {
  return (this->p == other.p);
}

template <size_t DIM>
bool Vector<DIM>::operator!=(const Vector<DIM> &other) const {
  return (this->p != other.p);
}

template <size_t DIM>
double Vector<DIM>::operator*(const Vector<DIM> &other) const {
  double result = 0;
  for (size_t i = 0; i < DIM; i++)
    result += this->p[i] * other.p[i];
  return result;
}

template <size_t DIM> Vector<DIM> Vector<DIM>::operator*(double k) const {
  return (Vector<DIM>(this->p * k));
}

template <size_t DIM> Vector<DIM> Vector<DIM>::operator/(double k) const {
  return (Vector<DIM>(this->p * (1/k)));
}

template <size_t DIM>
double Vector<DIM>::angle(const Vector<DIM> &v1, const Vector<DIM> &v2) {
  long double r = (v1 * v2) / (v1.mod() * v2.mod());
  long double rad = std::acos(r);
  return (rad * (180.0 / M_PIl));
}

template <size_t DIM> 
Vector<DIM> operator*(const double x, const Vector<DIM>&vec){
  return vec*x;
}

/* VectorRelation: TODO
static bool is_parallel(const Vector &, const Vector &);
static bool is_ortogonal(const Vector &, const Vector &);
static bool is_opposite(const Vector &, const Vector &);
static bool is_collinear(const Vector &, const Vector &);
static bool is_coplanar(const Vector &, const Vector &);
*/
