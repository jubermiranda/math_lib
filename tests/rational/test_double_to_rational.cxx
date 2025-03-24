#include <gtest/gtest.h>

#include "rational.h"


// This test file evaluates the Rational class constructor that takes a double parameter.
// The constructor aims to create a p/q representation approximating the given double value.
// Tests focus on verifying the accuracy and behavior of this approximation under various inputs.

const double kTolerance = 1e-10;

// simple double values that have exact representations as p/q
TEST(RationalFromDouble, SimpleExactDoubleToRational){
  Rational r;
  double n;

  n = 0.5;
  r = Rational(n);
  EXPECT_EQ(r.numerator(), 1);
  EXPECT_EQ(r.denominator(), 2);

  n = 0.25;
  r = Rational(n);
  EXPECT_EQ(r.numerator(), 1);
  EXPECT_EQ(r.denominator(), 4);

}
