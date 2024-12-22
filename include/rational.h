#ifndef RATIONAL_H_
#define RATIONAL_H_

#include <string>


class Rational {
public:
  Rational();
  Rational(int p, int q);
  Rational(int p, long q);
  Rational(long p, int q);
  Rational(long p, long q);
  Rational(unsigned p, unsigned q);

  Rational(int p, const Rational&q);
  Rational(long p, const Rational&q);
  Rational(double p, const Rational&q);
  Rational(const Rational& p, const Rational&q);

  Rational(unsigned);
  Rational(int);
  Rational(long);
  Rational(double);
  Rational(float);

  long numerator() const;
  long denominator() const;
  double decimal() const;

  long to_i() const;
  long to_l() const;
  float to_f() const;
  double to_d() const;
  long double to_ld() const;
  std::string to_s() const;

  bool is_positive() const { return sign; };

  Rational inverse() const;
  void update_denominator(const Rational&);

  Rational &operator=(const Rational &other);
  Rational operator+(const Rational &) const;
  Rational operator-(const Rational &) const;
  Rational operator*(const Rational &) const;
  Rational operator/(const Rational &) const;
  bool operator>(const Rational &) const;
  bool operator>=(const Rational &) const;
  bool operator<(const Rational &) const;
  bool operator<=(const Rational &) const;
  bool operator==(const Rational &) const;
  bool operator!=(const Rational &) const;

  Rational double_to_rational(double) const;

private:
  unsigned long p;
  unsigned long q;
  bool sign;

  void check_is_valid() const;
  bool same_sign(const Rational &) const;

  void simplify();
};

Rational operator+(long, const Rational &);
Rational operator+(const Rational &, long);
Rational operator+(int, const Rational &);
Rational operator+(const Rational &, int);
Rational operator+(double, const Rational &);
Rational operator+(const Rational &, double);
Rational operator-(long, const Rational &);
Rational operator-(const Rational &, long);
Rational operator-(int, const Rational &);
Rational operator-(const Rational &, int);
Rational operator-(double, const Rational &);
Rational operator-(const Rational &, double);
Rational operator-(const Rational &);
Rational operator*(long, const Rational &);
Rational operator*(const Rational &, long);
Rational operator*(int, const Rational &);
Rational operator*(const Rational &, int);
Rational operator*(double, const Rational &);
Rational operator*(const Rational &, double);
Rational operator/(long, const Rational &);
Rational operator/(const Rational &, long);
Rational operator/(int, const Rational &);
Rational operator/(const Rational &, int);
Rational operator/(double, const Rational &);
Rational operator/(const Rational &, double);

bool operator>(const Rational &, int);
bool operator>(const Rational &, long);
bool operator>(const Rational &, double);
bool operator>=(const Rational &, int);
bool operator>=(const Rational &, long);
bool operator>=(const Rational &, double);
bool operator<(const Rational &, int);
bool operator<(const Rational &, long);
bool operator<(const Rational &, double);
bool operator<=(const Rational &, int);
bool operator<=(const Rational &, long);
bool operator<=(const Rational &, double);

#endif
