#ifndef RATIONAL_H_
#define RATIONAL_H_

#include <string>

class Rational {
public:
  Rational();
  Rational(long p, long q);
  Rational(int p, int q);
  Rational(unsigned p, unsigned q);

  Rational(double);
  Rational(float);

  long numerator() const { return p; }
  long denominator() const { return q; }

  long to_l() const;
  double to_d() const;
  float to_f() const;
  std::string to_s() const;

private:
  long p;
  long q;
  bool sign;

  void check_is_valid() const;
  void simplify() ;
};

#endif
