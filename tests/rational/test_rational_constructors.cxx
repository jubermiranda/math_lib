#include <gtest/gtest.h>

#include "rational.h"
#include "../utils.h"

using std::string;

const double kTolerance = 1e-10;

// a empty constructors create a '0' Rational.
// in this impl, this is 0/1
TEST(RationalBasics, EmptyConstructor) {
  Rational r;

  r = Rational();

  ASSERT_EQ(r.numerator(), 0);
  ASSERT_EQ(r.denominator(), 1);

  ASSERT_EQ(static_cast<double>(r), 0.0);
  ASSERT_EQ(static_cast<long>(r), 0);
}

TEST(RationalBasics, IntegerParams) {
  Rational r;

  // null
  r = Rational();

  // p and q
  long p = 2;
  long q = 4;
  r = Rational(p, q);

  //int
  r = Rational(4);

  // decimal
  r = Rational(3.14159265359);

  // others
  r = Rational( Rational(1, 2) );
  r = Rational( 4, Rational(1, 3) );
  r = Rational( Rational(1,2), Rational(3,4) );
}
