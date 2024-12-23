#include <gtest/gtest.h>

#include "rational.h"
#include "utils.h"

using std::string;

const double kTolerance = 1e-10;

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

  //TODO:("others constructors")
}

TEST(RationalBasics, NumeratorDenominator){
  Rational r;

  r = Rational();
  EXPECT_EQ(r.numerator(), 0);

  r = Rational(4);
  EXPECT_EQ(r.numerator(), 4);
  EXPECT_EQ(r.denominator(), 1);

  r = Rational(16, 8);
  EXPECT_EQ(r.numerator(), 2);
  EXPECT_EQ(r.denominator(), 1);

  r = Rational(-16, 8);
  EXPECT_EQ(r.numerator(), 2);
  EXPECT_EQ(r.denominator(), 1);

  r = Rational(0.25);
  EXPECT_EQ(r.numerator(), 1);
  EXPECT_EQ(r.denominator(), 4);
  r = Rational(1.25);
  EXPECT_EQ(r.numerator(), 5);
  EXPECT_EQ(r.denominator(), 4);

  r = Rational(Rational(1, 2), Rational(3, 4));
  EXPECT_EQ(r.numerator(), 2);
  EXPECT_EQ(r.denominator(), 3);
}

TEST(RationalBasics, Decimal){
  // Rational.decimal should return the decimal part of the represented number p/q (converted to double)
  // sometimes, to_d() couldn't return the exact representation. so maybe its a approximation
  Rational r;

  double n = 3.14159265359;
  double expected_decimal_part = 0.14159265359;
  r = Rational(n);
  EXPECT_NEAR(r.decimal(), expected_decimal_part, kTolerance );

  r = Rational(1, 4);
  expected_decimal_part = 0.25;
  EXPECT_EQ(r.decimal(), expected_decimal_part);

  r = Rational(-1, 4);
  expected_decimal_part = -0.25;
  EXPECT_EQ(r.decimal(), expected_decimal_part);

  r = Rational(1);
  expected_decimal_part = 0;
  EXPECT_EQ(r.decimal(), expected_decimal_part);
}

TEST(RationalBasics, UpdateDenominator){
  Rational r(1, 7);
  r.update_denominator(r.denominator() + Rational(1, 3));

  EXPECT_EQ(r, Rational(3, 22));
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
