//std
#include <cmath>
#include <gtest/gtest.h>
#include <math.h>
#include <stdexcept>
#include <vector>

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
  lhs = u + (v+w);
  rhs = (u+v) + w;
  EXPECT_EQ(lhs, rhs);

  // Commutativity of addition: u + v = v + u
  lhs = u+v;
  rhs = v+u;
  EXPECT_EQ(lhs, rhs);
}

/*
 * u, v ∈ Vector
 * a, b ∈ ℝ (in our case, double)
*/
TEST(VectorProperties, MultplVec3) {
  Vector<3> u, v;
  double a, b;

  u = Vector<3>(22, 5, 31);
  v = Vector<3>(0, 9, 3);
  a = 4.9;
  b = -11;

  Vector<3> lhs, rhs;

  // a( u + v ) = au + av
  lhs = a * (u+v);
  rhs = a*u + a*v;
  EXPECT_EQ(lhs, rhs);
}
