#include <cmath>
#include <gtest/gtest.h>
#include <math.h>
#include <stdexcept>
#include <vector>

#include "utils.h"
#include "vector_lib.h"

using std::string;
const double kTolerance = 1e-10;

TEST(VectorBasics, Module) {
  Vector vec;

  vec = Vector(0, 0, 0);
  EXPECT_EQ(vec.mod(), 0);

  vec = Vector(2.4, 0, 0);
  EXPECT_EQ(vec.mod(), 2.4);
  vec = Vector(4.2, 0, 0);
  EXPECT_EQ(vec.mod(), 4.2);

  vec = Vector(0, 2, 0);
  EXPECT_EQ(vec.mod(), 2.0);
  vec = Vector(0, 4, 0);
  EXPECT_EQ(vec.mod(), 4.0);

  vec = Vector(0, 0, 2.2);
  EXPECT_EQ(vec.mod(), 2.2);
  vec = Vector(0, 0, 4.4);
  EXPECT_EQ(vec.mod(), 4.4);

  vec = Vector(1, 2, 2);
  EXPECT_EQ(vec.mod(), 3.0);

  vec = Vector(-3, -4, 0);
  EXPECT_EQ(vec.mod(), 5.0);
}

TEST(VectorBasics, ModuleSquare) {
  Vector vec;

  vec = Vector(1, 2, 2);
  EXPECT_EQ(vec.mod_square(), 9.0);

  vec = Vector(-3, -4, 0);
  EXPECT_EQ(vec.mod_square(), 25.0);
}

TEST(VectorBasics, IsNull) {
  Vector vec;

  vec = Vector(0, 0, 0);
  EXPECT_TRUE(vec.is_null());

  vec = Vector(1, 2, 3);
  EXPECT_FALSE(vec.is_null());
}

TEST(VectorBasics, IsUnit) {
  Vector vec;

  vec = Vector(1, 0, 0);
  EXPECT_TRUE(vec.is_unit());

  vec = Vector(0, 1, 0);
  EXPECT_TRUE(vec.is_unit());

  vec = Vector(0, 0, 1);
  EXPECT_TRUE(vec.is_unit());

  vec = Vector(-1, 0, 0);
  EXPECT_TRUE(vec.is_unit());

  vec = Vector(1, 2, 2);
  EXPECT_FALSE(vec.is_unit());
  // vec divided by its mod() results in unit vector
  Vector result = vec / vec.mod();
  EXPECT_TRUE(result.is_unit());
}

TEST(VectorBasics, Constructors) {
  Vector vec;
  Point p, q;

  vec = Vector();
  EXPECT_EQ(vec.x(), 0.0);
  EXPECT_EQ(vec.y(), 0.0);
  EXPECT_EQ(vec.z(), 0.0);
  EXPECT_TRUE(vec.is_null());

  p = Point(1, 2, 3);
  q = Point(5, 5, 5);
  EXPECT_EQ(Vector(p, q), Vector(q - p));

  vec = Vector(p, q);
  EXPECT_EQ(vec.x(), q.x - p.x);
  EXPECT_EQ(vec.y(), q.y - p.y);
  EXPECT_EQ(vec.z(), q.z - p.z);

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

  // factor = -1 keeps the same size. (change the direction)
  scale_factor = -1;
  vec_scaled = vec.scale(scale_factor);
  EXPECT_EQ(vec.opposite(), vec_scaled);
  EXPECT_TRUE(vec.mod() == vec_scaled.mod());
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

TEST(VectorBasics, OppositeVector) {
  Vector vec;
  Vector expected;

  vec = Vector(4, 2, 0);
  expected = Vector(-4, -2, 0);
  EXPECT_EQ(expected, vec.opposite());

  vec = Vector(0, 0, 0);
  expected = Vector(0, 0, 0);
  EXPECT_EQ(expected, vec.opposite());

  vec = Vector(-4, -3, -2);
  expected = Vector(4, 3, 2);
  EXPECT_EQ(expected, vec.opposite());

  vec = Vector(-1, 2, -3);
  expected = Vector(1, -2, 3);
  EXPECT_EQ(expected, vec.opposite());

  // sum of opposite vectors result in a null vector
  EXPECT_EQ((vec + vec.opposite()), Vector(0, 0, 0));
  EXPECT_TRUE((vec + vec.opposite()).is_null());
}

TEST(VectorBasics, RotateAroundX) {
  Vector vec;
  Vector expected;
  Vector result;
  double angle;

 // Rotate around X by 90 degrees
  angle = 90;

  vec = Vector(0, 1, 0);
  result = vec.rotate_around_x(angle);
  expected = Vector(0, 0, 1);
  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);

  vec = Vector(0, 0, 1);
  result = vec.rotate_around_x(angle);
  expected = Vector(0, -1, 0);
  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);
 //

 // Rotate around X by 180 degrees
  angle = 180;

  vec = Vector(0, 1, 0);
  result = vec.rotate_around_x(angle);
  expected = Vector(0, -1, 0);

  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);

  vec = Vector(1, 1, 1);
  result = vec.rotate_around_x(angle);
  expected = Vector(1, -1, -1);

  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);
 //
}

TEST(VectorBasics, RotateAroundY) {
  Vector vec;
  Vector expected;
  Vector result;
  double angle;

 // Rotate around Y by 90 degrees
  angle = 90;

  vec = Vector(1, 0, 0);
  result = vec.rotate_around_y(angle);
  expected = Vector(0, 0, -1);

  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);

  vec = Vector(0, 0, 1);
  result = vec.rotate_around_y(angle);
  expected = Vector(1, 0, 0);

  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);
 //

 // Rotate around Y by 180 degrees
  angle = 180;

  vec = Vector(1, 1, 1);
  result = vec.rotate_around_y(angle);
  expected = Vector(-1, 1, -1);

  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);
 //
}

TEST(VectorBasics, RotateAroundZ) {
  Vector vec;
  Vector expected;
  Vector result;
  double angle;

 // Rotate around Z by 90 degrees
  angle = 90;

  vec = Vector(1, 0, 0);
  result = vec.rotate_around_z(angle);
  expected = Vector(0, 1, 0);

  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);

  vec = Vector(0, 1, 0);
  result = vec.rotate_around_z(angle);
  expected = Vector(-1, 0, 0);

  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);
 //

 // Rotate around Z by 180 degrees
  angle = 180;

  vec = Vector(1, 1, 1);
  result = vec.rotate_around_z(angle);
  expected = Vector(-1, -1, 1);

  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);
 //
}
