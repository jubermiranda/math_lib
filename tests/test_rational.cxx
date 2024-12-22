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

  //int
  r = Rational(4);

  // decimal
  r = Rational(3.14159265359);
}

TEST(RationalBasics, UpdateDenominator){
  Rational r(1, 7);
  r.update_denominator(r.denominator() + Rational(1, 3));

  EXPECT_EQ(r, Rational(3, 22));
}

TEST(RationalBasics, numerator){
  Rational r;

  r = Rational();
  EXPECT_EQ(r.numerator(), 0);

  r = Rational(4);
  EXPECT_EQ(r.numerator(), 4);

  r = Rational(16, 8);
  EXPECT_EQ(r.numerator(), 2);

  r = Rational(-16, 8);
  EXPECT_EQ(r.numerator(), 2);

  r = Rational(0.25);
  EXPECT_EQ(r.numerator(), 1);
  r = Rational(1.25);
  EXPECT_EQ(r.numerator(), 5);
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
