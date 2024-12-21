#include <gtest/gtest.h>

#include "rational.h"
#include "utils.h"

using std::string;

TEST(RationalBasics, Constructors) {
  Rational r;

  // null
  r = Rational();

  // p and q
  long p = 2;
  long q = 4;
  r = Rational(p, q);

  // decimal
  //double d = 1.3333333333333;
  //r = Rational(d);
}

TEST(RationalBasics, Simplify){
  Rational r;

  r = Rational(100,42);
  EXPECT_EQ(r.numerator(), 50);
  EXPECT_EQ(r.denominator(), 21);

  r = Rational(126,294);
  EXPECT_EQ(r.numerator(), 3);
  EXPECT_EQ(r.denominator(), 7);
}

TEST(RationalBasics, OutPut) {
  Rational r;

  r = Rational(1, 2);
  EXPECT_EQ(r.to_d(), 1/2.0);
  EXPECT_EQ(r.to_f(), (float)(1/2.0));
  EXPECT_EQ(r.to_l(), 1/2);
  EXPECT_EQ(r.to_s(), "1/2");
}
