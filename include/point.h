#ifndef POINT_H_
#define POINT_H_

class Point {
public:
  double x;
  double y;
  double z;

  Point() : x(0), y(0), z(0){};
  Point(double x, double y, double z) : x(x), y(y), z(z){};
  Point(const Point &p) : x(p.x), y(p.y), z(p.z){};

  Point &operator=(const Point &);
  Point operator-(const Point &) const;
  Point operator+(const Point &) const;
  Point operator*(double scalar) const;
  bool operator==(const Point &) const;
  bool operator!=(const Point &) const;
};

#endif /* ifndef POINT_H_ */
