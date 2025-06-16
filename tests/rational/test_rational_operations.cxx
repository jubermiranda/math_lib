#include <gtest/gtest.h>

#include "rational.h"
#include "../utils.h"

using std::string;

const double kTolerance = 1e-10;

// TODO: improve rational tests

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
  // Rational.decimal should return the decimal part 
  // of the represented number p/q (converted to double)
  // sometimes double couldn't represent the exact value. 
  // so maybe its a approximation
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

TEST(RationalBasics, Convertions){
  Rational r;

  r = Rational(5, 4);
  EXPECT_EQ(static_cast<long>(r), 1);
  EXPECT_EQ(static_cast<double>(r), 1.25);
  EXPECT_EQ(r.to_s(), "5/4");

  r = Rational(-5, 4);
  EXPECT_EQ(static_cast<long>(r), -1);
  EXPECT_EQ(static_cast<double>(r), -1.25);
  EXPECT_EQ(r.to_s(), "-5/4");

  r = Rational(0, 4);
  EXPECT_EQ(static_cast<long>(r), (long)0);
  EXPECT_EQ(static_cast<double>(r), (double)0.0);
  EXPECT_EQ(r.to_s(), "0");

  r = Rational(0, -2);
  EXPECT_EQ(static_cast<long>(r), (long)0);
  EXPECT_EQ(static_cast<double>(r), (double)0.0);
  EXPECT_EQ(r.to_s(), "0");
}

TEST(RationalBasics, IsPositive){
  Rational r;

  r = Rational(4, 2);
  EXPECT_TRUE(r.is_positive());
  // in this impl, 0 return true to is_positive
  r = Rational(0);
  EXPECT_TRUE(r.is_positive());

  r = Rational(-2, 4);
  EXPECT_FALSE(r.is_positive());
  r = Rational(2, -4);
  EXPECT_FALSE(r.is_positive());
}

TEST(RationalBasics, Inverse){
  Rational r;

  r = Rational(3,7);
  EXPECT_EQ(r.numerator(), r.inverse().denominator());
  EXPECT_EQ(r.denominator(), r.inverse().numerator());
  EXPECT_EQ(r.inverse(), Rational(7, 3));
}

TEST(RationalBasics, UpdateDenominator){
  Rational r(1, 7);
  r.update_denominator(r.denominator() + Rational(1, 3));

  EXPECT_EQ(r, Rational(3, 22));
}

TEST(RationalBasics, Sum){
  Rational n1, n2;

  n1 = Rational(1, 2);
  n2 = Rational(3, 2);
  EXPECT_EQ(n1 + n2, Rational(4, 2));
  EXPECT_EQ(n1 + n2, Rational(2));

  n1 = Rational(7);
  n2 = Rational(3);
  EXPECT_EQ(n1 + n2, Rational(10));
  n2 = Rational(-3);
  EXPECT_EQ(n1 + n2, Rational(4));

  n1 = Rational(0.75);
  n2 = Rational(0.25);
  EXPECT_EQ(n1 + n2, Rational(1));
  n2 = Rational(-0.25);
  EXPECT_EQ(n1 + n2, Rational(0.5));
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

