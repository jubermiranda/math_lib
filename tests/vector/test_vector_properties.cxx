// std
#include <cmath>
#include <gtest/gtest.h>
#include <math.h>

#include "vector_lib.h"

/*
 * Test section for mathematical properties of vector operations
 * Verifies key algebraic properties such as
 * associativity, commutativity, distributivity, etc
 */

using std::string;
const double kTolerance = 1e-10;

const size_t STD_V_DIM = 3;

TEST(VectorProperties, SumVec3) {
  Vector<3> u, v, w;
  Vector<3> lhs, rhs;
  u = Vector<3>(1, 3, 5);
  v = Vector<3>(7, 11, 16);
  w = Vector<3>(-4, 0, -2);

  // Associativity of addition: u+(v+w) = (u+v)+w
  lhs = u + (v + w);
  rhs = (u + v) + w;
  EXPECT_EQ(lhs, rhs);

  // Commutativity of addition: u + v = v + u
  lhs = u + v;
  rhs = v + u;
  EXPECT_EQ(lhs, rhs);
}

/*
 * u, v ∈ Vector
 * a, b ∈ ℝ (in our case, double)
 *
 * Note: Due to floating-point arithmetic, small rounding errors may occur
 * with doubles.
 * Thus, EXPECT_NEAR is used instead of EXPECT_EQ to account for precision
 * differences.
 */
TEST(VectorProperties, MultplVec3) {
  Vector<3> u, v;
  double a, b;

  u = Vector<3>(22, 5, 31);
  v = Vector<3>(0, 9, 3);

  Vector<3> lhs, rhs;

  /*
   * a( u + v ) = au + av
   */
  a = 4;
  b = -11;
  lhs = a * (u + v);
  rhs = (a * u) + (a * v);
  EXPECT_EQ(lhs, rhs);

  a = 3.14159265359;
  b = 1.41421356237;
  lhs = a * (u + v);
  rhs = a * u + a * v;
  EXPECT_NEAR(lhs.coord(0), rhs.coord(0), kTolerance);
  EXPECT_NEAR(lhs.coord(1), rhs.coord(1), kTolerance);
  EXPECT_NEAR(lhs.coord(2), rhs.coord(2), kTolerance);

  /*
   * (a + b)u = au + bu
   */
  lhs = (a + b) * u;
  rhs = a*u + b*u;
  EXPECT_NEAR(lhs.coord(0), rhs.coord(0), kTolerance);
  EXPECT_NEAR(lhs.coord(1), rhs.coord(1), kTolerance);
  EXPECT_NEAR(lhs.coord(2), rhs.coord(2), kTolerance);

  /*
   * (ab)u = a(bu) 
   */
  lhs = (a*b)*u;
  rhs = a*(b*u);
  EXPECT_NEAR(lhs.coord(0), rhs.coord(0), kTolerance);
  EXPECT_NEAR(lhs.coord(1), rhs.coord(1), kTolerance);
  EXPECT_NEAR(lhs.coord(2), rhs.coord(2), kTolerance);

  /*
   * 1*u = u
   */
  lhs = 1 * u;
  rhs = u;
  EXPECT_EQ(lhs, rhs);
}
