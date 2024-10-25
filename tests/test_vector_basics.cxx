#include <gtest/gtest.h>
#include <math.h>
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

  vec = Vector(3.0, 4.0, 0.0);
  expect_unit = Vector(0.6, 0.8, 0);

  EXPECT_EQ(expect_unit, vec.unit());
}

TEST(VectorBasics, ScaleVector) {
  Vector vec(4, 3, 2);
  Vector vec_scaled;
  float scale_factor;

  scale_factor = 3.5;
  EXPECT_EQ(vec.scale(scale_factor), Vector(14, 10.5, 7));

  scale_factor = -1;
  EXPECT_EQ(vec.scale(scale_factor), Vector(-4, -3, -2));

  scale_factor = 0;
  EXPECT_EQ(vec.scale(scale_factor), Vector(0, 0, 0));
  EXPECT_TRUE(vec.scale(scale_factor).is_null());

  // 0 < factor < 1 should makes the vector shorter
  scale_factor = 0.5;
  vec_scaled = vec.scale(scale_factor);
  EXPECT_TRUE(vec.mod() > vec_scaled.mod());

  // factor > 1 should makes the vector longer
  scale_factor = 42;
  vec_scaled = vec.scale(scale_factor);
  EXPECT_TRUE(vec.mod() < vec_scaled.mod());
}

TEST(VectorBasics, DirectionCossines) {
  Vector vec;
  Vector expected;

  vec = Vector(3, 4, 0);
  expected = Vector(0.6, 0.8, 0.0);
  EXPECT_EQ(expected, vec.direction_cossines());

  vec = Vector(1, 0, 0);
  expected = Vector(1, 0, 0);
  EXPECT_EQ(expected, vec.direction_cossines());

  vec = Vector(0, 1, 0);
  expected = Vector(0, 1, 0);
  EXPECT_EQ(expected, vec.direction_cossines());

  vec = Vector(0, 0, 1);
  expected = Vector(0, 0, 1);
  EXPECT_EQ(expected, vec.direction_cossines());

  vec = Vector(1, 1, 1);
  expected = Vector(1 / std::sqrt(3), 1 / std::sqrt(3), 1 / std::sqrt(3));
  EXPECT_EQ(expected, vec.direction_cossines());

  // vector with same values (x,y,z) result equals cossines
  vec = Vector(42, 42, 42);
  Vector cossines = vec.direction_cossines();
  EXPECT_EQ(cossines.x(), cossines.y());
  EXPECT_EQ(cossines.x(), cossines.z());
}
