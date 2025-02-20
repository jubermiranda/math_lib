#ifndef POINT_H_
#define POINT_H_

#include <array>
#include <cstddef>

template <size_t DIM> class Point {
public:
  std::array<double, DIM> coords;

  template <typename... Args>
  Point(Args... args) : coords{static_cast<double>(args)...} {
    static_assert(sizeof...(args) == DIM, "Invalid number of arguments");
  }
  Point(const Point &);
  Point();

  Point &operator=(const Point &);
  Point operator-(const Point &) const;
  Point operator+(const Point &) const;
  Point operator*(double scalar) const;
  bool operator==(const Point &) const;
  bool operator!=(const Point &) const;
};

// TODO: include tpp impl file

#endif /* ifndef POINT_H_ */
