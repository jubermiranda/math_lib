#ifndef RATIONAL_H_
#define RATIONAL_H_

#include <string>

class Rational {
public:
  Rational();
  Rational(const Rational&);

  Rational(long p, long q);
  Rational(long p, const Rational &q);
  Rational(const Rational &p, const Rational &q);

  explicit Rational(int);
  explicit Rational(long);
  explicit Rational(double);

  long numerator() const;
  long denominator() const;
  double decimal() const;

  std::string to_s() const;

  bool is_positive() const { return sign; };

  Rational inverse() const;
  void update_denominator(const Rational &);

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

  explicit operator long() const;
  explicit operator unsigned long() const;
  explicit operator double() const;


private:
  unsigned long p;
  unsigned long q;
  bool sign;

  void init_attr(long p, long q);
  void check_is_valid() const;
  bool same_sign(const Rational &) const;
  Rational double_to_rational(double) const;

  void simplify();
};

Rational operator+(double, const Rational &);
Rational operator+(const Rational &, double);

Rational operator-(double, const Rational &);
Rational operator-(const Rational &, double);

Rational operator*(double, const Rational &);
Rational operator*(const Rational &, double);

Rational operator/(double, const Rational &);
Rational operator/(const Rational &, double);

bool operator>(const Rational &, double);
bool operator>(double, const Rational &);

bool operator>=(const Rational &, double);
bool operator>=(double, const Rational &);

bool operator<(const Rational &, double);
bool operator<(double, const Rational &);

bool operator<=(const Rational &, double);
bool operator<=(double, const Rational &);

bool operator==(const Rational &, double);
bool operator==(double, const Rational &);

bool operator!=(const Rational &, double);
bool operator!=(double, const Rational &);

#endif
