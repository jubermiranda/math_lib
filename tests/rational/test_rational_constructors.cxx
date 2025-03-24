#include <gtest/gtest.h>

#include "../utils.h"
#include "rational.h"

/*
 * Rational class represents a rational number in form: p/q
 *
 * - some constructors with parameters of basic numeric types(long, double, etc)
 *   and/or other obj of this class.
 *
 * - Any p/q representation will be simplified to its most resuced form
 *   with the resulting sign stored separately;
 *   thus, p and q are always unsigned numbers.
 *
 */

const double kTolerance = 1e-10;

// a empty constructors create a '0' Rational.
// in this impl, this is 0/1
TEST(RationalConstructors, Empty) {
  Rational r;

  r = Rational();

  ASSERT_EQ(r.numerator(), 0);
  ASSERT_EQ(r.denominator(), 1);
}

// equals params p and q create a '1' Rational.
// ∀(p, q)((p, q: long) and (p == q)) -> Rational(p, q): p = 1, q = 1
TEST(RationalConstructors, IntegerEqualsParams) {
  Rational r;
  long p, q;

  p = 1;
  r = Rational(p, p);
  ASSERT_EQ(r.numerator(), 1);
  ASSERT_EQ(r.denominator(), 1);

  p = 3;
  r = Rational(p, p);
  ASSERT_EQ(r.numerator(), 1);
  ASSERT_EQ(r.denominator(), 1);

  p = -9;
  r = Rational(p, p);
  ASSERT_EQ(r.numerator(), 1);
  ASSERT_EQ(r.denominator(), 1);
}

// params p: long, q: long, represents rational p/q (q != 0)
TEST(RationalConstructors, IntegerDiferentParams) {
  Rational r;
  long p, q;

  p = 1;
  q = 2;
  r = Rational(p, q);
  ASSERT_EQ(r.numerator(), 1);
  ASSERT_EQ(r.denominator(), 2);

  // ∀(p, q)(p == 0) -> q = 1
  p = 0;

  q = 4;
  r = Rational(p, q);
  ASSERT_EQ(r.numerator(), 0);
  ASSERT_EQ(r.denominator(), 1);

  q = 16;
  r = Rational(p, q);
  ASSERT_EQ(r.numerator(), 0);
  ASSERT_EQ(r.denominator(), 1);
}
