#ifndef RATIONAL_H_
#define RATIONAL_H_

#include <string>

class Rational {
public:
  Rational();
  Rational(long p, long q);
  Rational(int p, int q);
  Rational(unsigned p, unsigned q);

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

private:
  unsigned long p;
  unsigned long q;
  bool sign;

  void check_is_valid() const;
  bool same_sign(const Rational &) const;

  void simplify();
  void decimal_to_pq(double);
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
