#ifndef POINT_H_
#define POINT_H_

class Point {
public:
  float x;
  float y;
  float z;

  Point(float x, float y, float z) : x(x), y(y), z(z) {}
  Point():x(0),y(0),z(0){};

  Point operator-(const Point&)const;
  Point operator+(const Point&)const;
  bool operator==(const Point&)const;
};

#endif /* ifndef POINT_H_ */
