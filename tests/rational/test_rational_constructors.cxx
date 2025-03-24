#include <gtest/gtest.h>

#include "rational.h"
#include "../utils.h"

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
