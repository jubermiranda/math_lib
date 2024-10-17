#include "vector_lib.h"

Vector::Vector() : p(Point(0, 0, 0)) {}

Vector::Vector(Point p) : p(p) {}

Vector::Vector(Point a, Point b) : p(b - a) {}

Vector::Vector(float x, float y, float z) : p(Point(x, y, z)) {}





/* VectorRelation: TODO
static bool is_parallel(const Vector &, const Vector &);
static bool is_ortogonal(const Vector &, const Vector &);
static bool is_opposite(const Vector &, const Vector &);
static bool is_collinear(const Vector &, const Vector &);
static bool is_coplanar(const Vector &, const Vector &);
*/
