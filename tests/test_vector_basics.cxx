#include <cmath>
#include <gtest/gtest.h>
#include <math.h>
#include <stdexcept>
#include <vector>

#include "utils.h"
#include "vector_lib.h"

using std::string;
const double kTolerance = 1e-10;

const size_t STD_V_DIM = 3;

TEST(VectorBasics, Constructors) {
  Vector<STD_V_DIM> vec;
  Point<STD_V_DIM> p, q;

  // empty constructor
  vec = Vector<STD_V_DIM>();
  EXPECT_EQ(vec.coord(0), 0.0);
  EXPECT_EQ(vec.coord(1), 0.0);
  EXPECT_EQ(vec.coord(2), 0.0);
  EXPECT_TRUE(vec.is_null());

  // point constructor 
  p = Point<STD_V_DIM>(1, 2, 3);
  q = Point<STD_V_DIM>(5, 5, 5);
  
  // using 2 points, vector result is p2 - p1
  vec = Vector<STD_V_DIM>(p, q);
  EXPECT_EQ(vec, Vector<STD_V_DIM>(q - p));
  EXPECT_EQ(vec.coord(0), q[0] - p[0]);
  EXPECT_EQ(vec.coord(1), q[1] - p[1]);
  EXPECT_EQ(vec.coord(2), q[2] - p[2]);
}

TEST(VectorBasics, Module) {
  Vector<STD_V_DIM> vec;

  vec = Vector<STD_V_DIM>(0, 0, 0);
  EXPECT_EQ(vec.mod(), 0);

  vec = Vector<STD_V_DIM>(2.4, 0, 0);
  EXPECT_EQ(vec.mod(), 2.4);
  vec = Vector<STD_V_DIM>(4.2, 0, 0);
  EXPECT_EQ(vec.mod(), 4.2);

  vec = Vector<STD_V_DIM>(0, 2, 0);
  EXPECT_EQ(vec.mod(), 2.0);
  vec = Vector<STD_V_DIM>(0, 4, 0);
  EXPECT_EQ(vec.mod(), 4.0);

  vec = Vector<STD_V_DIM>(0, 0, 2.2);
  EXPECT_EQ(vec.mod(), 2.2);
  vec = Vector<STD_V_DIM>(0, 0, 4.4);
  EXPECT_EQ(vec.mod(), 4.4);

  vec = Vector<STD_V_DIM>(1, 2, 2);
  EXPECT_EQ(vec.mod(), 3.0);

  vec = Vector<STD_V_DIM>(-3, -4, 0);
  EXPECT_EQ(vec.mod(), 5.0);
}

TEST(VectorBasics, ModuleSquare) {
  Vector<STD_V_DIM> vec;

  vec = Vector<STD_V_DIM>(1, 2, 2);
  EXPECT_EQ(vec.mod_square(), 9.0);

  vec = Vector<STD_V_DIM>(-3, -4, 0);
  EXPECT_EQ(vec.mod_square(), 25.0);
}

TEST(VectorBasics, IsNull) {
  Vector<STD_V_DIM> vec;

  vec = Vector<STD_V_DIM>(0, 0, 0);
  EXPECT_TRUE(vec.is_null());

  vec = Vector<STD_V_DIM>(1, 2, 3);
  EXPECT_FALSE(vec.is_null());
}

TEST(VectorBasics, UnitVector) {
  Vector<STD_V_DIM> vec, expect_unit;

  vec = Vector<STD_V_DIM>(1, 0, 0);
  EXPECT_TRUE(vec.is_unit());

  vec = Vector<STD_V_DIM>(0, 1, 0);
  EXPECT_TRUE(vec.is_unit());

  vec = Vector<STD_V_DIM>(0, 0, 1);
  EXPECT_TRUE(vec.is_unit());

  vec = Vector<STD_V_DIM>(-1, 0, 0);
  EXPECT_TRUE(vec.is_unit());

  vec = Vector<STD_V_DIM>(1, 2, 2);
  EXPECT_FALSE(vec.is_unit());

  vec = Vector<STD_V_DIM>(3.0, 4.0, 0.0);
  expect_unit = Vector<STD_V_DIM>(0.6, 0.8, 0);
  EXPECT_NEAR(expect_unit.coord(0), vec.unit().coord(0), kTolerance);
  EXPECT_NEAR(expect_unit.coord(1), vec.unit().coord(1), kTolerance);
  EXPECT_NEAR(expect_unit.coord(2), vec.unit().coord(2), kTolerance);

  EXPECT_TRUE( vec.unit().is_unit() );
  EXPECT_TRUE( vec.unit().mod() == 1 );

  // divide a vector by its mod result in a unit vector
  vec = Vector<STD_V_DIM>(4,3,2);
  expect_unit = vec / vec.mod();
  EXPECT_EQ( expect_unit, vec.unit());
  EXPECT_TRUE( expect_unit.mod() == 1 );

  vec = Vector<STD_V_DIM>(-5,3,-1);
  expect_unit = vec / vec.mod();
  EXPECT_EQ( expect_unit, vec.unit());
  EXPECT_NEAR( expect_unit.mod(), 1, kTolerance);

  vec = Vector<STD_V_DIM>(0.41, 2.99, 3.1);
  expect_unit = vec / vec.mod();
  EXPECT_EQ( expect_unit, vec.unit());
  // round error here, so use a tolerance
  EXPECT_NEAR( expect_unit.mod(), 1, kTolerance );
}

TEST(VectorBasics, ScaleVector) {
  Vector<STD_V_DIM> vec(4, 3, 2);
  Vector<STD_V_DIM> vec_scaled;
  float scale_factor;

  scale_factor = 3.5;
  EXPECT_EQ(vec.scale(scale_factor), Vector<STD_V_DIM>(14, 10.5, 7));

  scale_factor = -1;
  EXPECT_EQ(vec.scale(scale_factor), Vector<STD_V_DIM>(-4, -3, -2));

  scale_factor = 0;
  EXPECT_EQ(vec.scale(scale_factor), Vector<STD_V_DIM>(0, 0, 0));
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

TEST(VectorBasics, Operators){
  Vector<STD_V_DIM> u, v, w, expected;

  // sum - diff
  v = Vector<STD_V_DIM>(1, 3, 5);
  w = Vector<STD_V_DIM>(1, 1, 1);
  expected = Vector<STD_V_DIM>(2, 4, 6);
  EXPECT_EQ( expected, v + w );
  EXPECT_EQ( v + w, w + v );

  expected = Vector<STD_V_DIM>(0, 2, 4);
  EXPECT_EQ( v - w, expected );
  expected = Vector<STD_V_DIM>(0, -2, -4);
  EXPECT_EQ( w - v, expected );

  // * /
  v = Vector<STD_V_DIM>(3, 4, 0);
  EXPECT_EQ( v.mod(), 5 );
  EXPECT_EQ( (v * 0.5), (v / 2) );
  v = v * 2;
  EXPECT_EQ( v.mod(), 10);
  v = v * (1.0/2);
  EXPECT_EQ( v.mod(), 5);

  EXPECT_EQ( v * -1, v.opposite() );

  // u( v + w ) === u.v + u.w
  double lhs, rhs;
  lhs = u * (v + w);
  rhs = u * v + u * w;
  EXPECT_EQ( lhs, rhs );

  // u * v === v * u
  EXPECT_EQ( v*u, u*v );

  // k(u * v) === (ku) * v
  double k = 42;
  lhs = k * ( u * v );
  rhs = (u * k) * v;
  EXPECT_EQ(lhs, rhs);

  // u * u === |u|^2
  EXPECT_EQ( u * u, u.mod() * u.mod() );
}

TEST(VectorBasics, DirectionCossines) {
  Vector<STD_V_DIM> vec;
  Vector<STD_V_DIM> expected;

  vec = Vector<STD_V_DIM>(3, 4, 0);
  expected = Vector<STD_V_DIM>(0.6, 0.8, 0.0);
  EXPECT_EQ(expected, vec.direction_cossines());

  vec = Vector<STD_V_DIM>(1, 0, 0);
  expected = Vector<STD_V_DIM>(1, 0, 0);
  EXPECT_EQ(expected, vec.direction_cossines());

  vec = Vector<STD_V_DIM>(0, 1, 0);
  expected = Vector<STD_V_DIM>(0, 1, 0);
  EXPECT_EQ(expected, vec.direction_cossines());

  vec = Vector<STD_V_DIM>(0, 0, 1);
  expected = Vector<STD_V_DIM>(0, 0, 1);
  EXPECT_EQ(expected, vec.direction_cossines());

  vec = Vector<STD_V_DIM>(1, 1, 1);
  expected = Vector<STD_V_DIM>(1 / std::sqrt(3), 1 / std::sqrt(3), 1 / std::sqrt(3));
  EXPECT_EQ(expected, vec.direction_cossines());

  // vector with same values (x,y,z) result equals cossines
  vec = Vector<STD_V_DIM>(42, 42, 42);
  Vector<STD_V_DIM> cossines = vec.direction_cossines();
  EXPECT_EQ(cossines.coord(0), cossines.coord(1));
  EXPECT_EQ(cossines.coord(0), cossines.coord(2));
}

TEST(VectorBasics, OppositeVector) {
  Vector<STD_V_DIM> vec;
  Vector<STD_V_DIM> expected;

  vec = Vector<STD_V_DIM>(4, 2, 0);
  expected = Vector<STD_V_DIM>(-4, -2, 0);
  EXPECT_EQ(expected, vec.opposite());

  vec = Vector<STD_V_DIM>(0, 0, 0);
  expected = Vector<STD_V_DIM>(0, 0, 0);
  EXPECT_EQ(expected, vec.opposite());

  vec = Vector<STD_V_DIM>(-4, -3, -2);
  expected = Vector<STD_V_DIM>(4, 3, 2);
  EXPECT_EQ(expected, vec.opposite());

  vec = Vector<STD_V_DIM>(-1, 2, -3);
  expected = Vector<STD_V_DIM>(1, -2, 3);
  EXPECT_EQ(expected, vec.opposite());

  // sum of opposite vectors result in a null vector
  EXPECT_EQ((vec + vec.opposite()), Vector<STD_V_DIM>(0, 0, 0));
  EXPECT_TRUE((vec + vec.opposite()).is_null());
}

/*
 * TODO
TEST(VectorBasics, RotateAroundX) {
  Vector<STD_V_DIM> vec;
  Vector<STD_V_DIM> expected;
  Vector<STD_V_DIM> result;
  double angle;

 // Rotate around X by 90 degrees
  angle = 90;

  vec = Vector<STD_V_DIM>(0, 1, 0);
  result = vec.rotate_around_x(angle);
  expected = Vector<STD_V_DIM>(0, 0, 1);
  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);

  vec = Vector<STD_V_DIM>(0, 0, 1);
  result = vec.rotate_around_x(angle);
  expected = Vector<STD_V_DIM>(0, -1, 0);
  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);
 //

 // Rotate around X by 180 degrees
  angle = 180;

  vec = Vector<STD_V_DIM>(0, 1, 0);
  result = vec.rotate_around_x(angle);
  expected = Vector<STD_V_DIM>(0, -1, 0);

  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);

  vec = Vector<STD_V_DIM>(1, 1, 1);
  result = vec.rotate_around_x(angle);
  expected = Vector<STD_V_DIM>(1, -1, -1);

  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);
 //
}

TEST(VectorBasics, RotateAroundY) {
  Vector<STD_V_DIM> vec;
  Vector<STD_V_DIM> expected;
  Vector<STD_V_DIM> result;
  double angle;

 // Rotate around Y by 90 degrees
  angle = 90;

  vec = Vector<STD_V_DIM>(1, 0, 0);
  result = vec.rotate_around_y(angle);
  expected = Vector<STD_V_DIM>(0, 0, -1);

  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);

  vec = Vector<STD_V_DIM>(0, 0, 1);
  result = vec.rotate_around_y(angle);
  expected = Vector<STD_V_DIM>(1, 0, 0);

  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);
 //

 // Rotate around Y by 180 degrees
  angle = 180;

  vec = Vector<STD_V_DIM>(1, 1, 1);
  result = vec.rotate_around_y(angle);
  expected = Vector<STD_V_DIM>(-1, 1, -1);

  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);
 //
}

TEST(VectorBasics, RotateAroundZ) {
  Vector<STD_V_DIM> vec;
  Vector<STD_V_DIM> expected;
  Vector<STD_V_DIM> result;
  double angle;

 // Rotate around Z by 90 degrees
  angle = 90;

  vec = Vector<STD_V_DIM>(1, 0, 0);
  result = vec.rotate_around_z(angle);
  expected = Vector<STD_V_DIM>(0, 1, 0);

  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);

  vec = Vector<STD_V_DIM>(0, 1, 0);
  result = vec.rotate_around_z(angle);
  expected = Vector<STD_V_DIM>(-1, 0, 0);

  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);
 //

 // Rotate around Z by 180 degrees
  angle = 180;

  vec = Vector<STD_V_DIM>(1, 1, 1);
  result = vec.rotate_around_z(angle);
  expected = Vector<STD_V_DIM>(-1, -1, 1);

  EXPECT_NEAR(result.x(), expected.x(), kTolerance);
  EXPECT_NEAR(result.y(), expected.y(), kTolerance);
  EXPECT_NEAR(result.z(), expected.z(), kTolerance);
 //
}
*/

TEST(VectorBasics, Angle){
  double lhs, rhs;
  Vector<STD_V_DIM> v, w;

  v = Vector<STD_V_DIM>(1, 0, 0);
  w = Vector<STD_V_DIM>(0, 1, 0);
  lhs = 90;
  rhs = Vector<STD_V_DIM>::angle(v, w);
  EXPECT_NEAR(lhs, rhs, kTolerance);

  v = Vector<STD_V_DIM>(1, 0, 0);
  w = Vector<STD_V_DIM>(1, 0, 0);
  lhs = 0;
  rhs = Vector<STD_V_DIM>::angle(v, w);
  EXPECT_NEAR(lhs, rhs, kTolerance);

  v = Vector<STD_V_DIM>(sqrt(3), 1, 0);
  w = Vector<STD_V_DIM>(2, 0, 0);
  lhs = 30;
  rhs = Vector<STD_V_DIM>::angle(v, w);
  EXPECT_NEAR(lhs, rhs, kTolerance);

  v = Vector<STD_V_DIM>(1, 1, 0);
  w = Vector<STD_V_DIM>(1, 0, 0);
  lhs = 45;
  rhs = Vector<STD_V_DIM>::angle(v, w);
  EXPECT_NEAR(lhs, rhs, kTolerance);

  v = Vector<STD_V_DIM>(1, sqrt(3), 0);
  w = Vector<STD_V_DIM>(2, 0, 0);
  lhs = 60;
  rhs = Vector<STD_V_DIM>::angle(v, w);
  EXPECT_NEAR(lhs, rhs, kTolerance);
}

