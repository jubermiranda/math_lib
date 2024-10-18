#include <gtest/gtest.h>
#include <vector>

#include "utils.h"
#include "vector_lib.h"

using std::string;

TEST(VectorBasics, Module) {
  Vector vec;

  vec = Vector(0, 0, 0);
  EXPECT_EQ(vec.mod(), 0);

  vec = Vector(2.4, 0, 0);
  EXPECT_EQ(vec.mod(), 2.4f);
  vec = Vector(4.2, 0, 0);
  EXPECT_EQ(vec.mod(), 4.2f);

  vec = Vector(0, 2, 0);
  EXPECT_EQ(vec.mod(), 2.0f);
  vec = Vector(0, 4, 0);
  EXPECT_EQ(vec.mod(), 4.0f);

  vec = Vector(0, 0, 2.2);
  EXPECT_EQ(vec.mod(), 2.2f);
  vec = Vector(0, 0, 4.4);
  EXPECT_EQ(vec.mod(), 4.4f);

  vec = Vector(1, 2, 2);
  EXPECT_EQ(vec.mod(), 3.0f);

  vec = Vector(-3, -4, 0);
  EXPECT_EQ(vec.mod(), 5.0f);
}

TEST(VectorBasics, ModuleSquare) {
  Vector vec;

  vec = Vector(1, 2, 2);
  EXPECT_EQ(vec.mod_square(), 9.0f);

  vec = Vector(-3, -4, 0);
  EXPECT_EQ(vec.mod_square(), 25.0f);
}

TEST(VectorBasics, Constructors) {
  Vector vec;
  Point p, q;

  vec = Vector();
  EXPECT_EQ(vec.x(), 0.0f);
  EXPECT_EQ(vec.y(), 0.0f);
  EXPECT_EQ(vec.z(), 0.0f);
  EXPECT_TRUE(vec.is_null());

  p = Point(1, 2, 3);
  q = Point(5, 5, 5);
  vec = Vector(p, q);
  EXPECT_EQ(vec.x(), q.x - p.x);
  EXPECT_EQ(vec.y(), q.y - p.y);
  EXPECT_EQ(vec.z(), q.z - p.z);

  EXPECT_EQ(Vector(p, q), Vector(q - p));

  EXPECT_EQ(Vector(Point(7, 7, 7)), Vector(7, 7, 7));
}

TEST(VectorBasics, UnitVector) {
  Vector vec, expect_unit;
  float vec_mod;

  vec = Vector(2.0, 4.0, 6.0);
  vec_mod = vec.mod();
  expect_unit = Vector(vec.x() / vec_mod, vec.y() / vec_mod, vec.z() / vec_mod);

  EXPECT_EQ(expect_unit, vec.unit());
}
