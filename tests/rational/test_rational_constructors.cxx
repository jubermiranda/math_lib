#include <gtest/gtest.h>

#include "../utils.h"
#include "rational.h"

using std::string;

const double kTolerance = 1e-10;

// a empty constructors create a '0' Rational.
// in this impl, this is 0/1
TEST(RationalConstructors, Empty) {
  Rational r;

  r = Rational();

  ASSERT_EQ(r.numerator(), 0);
  ASSERT_EQ(r.denominator(), 1);

  ASSERT_EQ(static_cast<double>(r), 0.0);
  ASSERT_EQ(static_cast<long>(r), 0);
}

// equals params p and q create a '1' Rational.
// this impl should ever simplify, then:
// ∀(p, q)((p, q ∈ long) and (p == q)) -> Rational(p, q): p = 1, q = 1
TEST(RationalConstructors, IntegerEqualsParams) {
  Rational r;
  long p, q;

  p = 1;
  r = Rational(p, p);
  ASSERT_EQ(r.numerator(), 1);
  ASSERT_EQ(r.denominator(), 1);
  ASSERT_EQ(static_cast<long>(r), 1);

  p = 3;
  r = Rational(p, p);
  ASSERT_EQ(r.numerator(), 1);
  ASSERT_EQ(r.denominator(), 1);
  ASSERT_EQ(static_cast<long>(r), 1);

  p = -9;
  r = Rational(p, p);
  ASSERT_EQ(r.numerator(), 1);
  ASSERT_EQ(r.denominator(), 1);
  ASSERT_EQ(static_cast<long>(r), 1);
}
