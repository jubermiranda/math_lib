#include "rational.h"
#include <cmath>
#include <numbers>
#include <stdexcept>
#include <string>

long mdc_euc(long a, long b);
Rational cont_fraction(double n);

Rational::Rational() : p(0), q(1), sign(true){};

Rational::Rational(long p, long q) : p(p), q(q), sign((p * q >= 0)) {
  check_is_valid();
  simplify();
}

Rational::Rational(int p, int q) : p(p), q(q), sign((p * q >= 0)) {
  check_is_valid();
  simplify();
}

Rational::Rational(unsigned p, unsigned q) : p(p), q(q), sign(true) {
  check_is_valid();
  simplify();
}

Rational::Rational(unsigned n) {
  this->sign = true;
  p = n;
  q = 1;
}

Rational::Rational(long n) {
  this->sign = (n >= 0);
  p = n;
  q = 1;
}

Rational::Rational(int n) {
  this->sign = (n >= 0);
  p = n;
  q = 1;
}

Rational::Rational(double n) { decimal_to_pq(n); }

Rational::Rational(float n) { decimal_to_pq(n); }

long Rational::numerator() const { return (sign) ? p : -p; }

long Rational::denominator() const { return q; }

double Rational::decimal() const {
  double int_part;
  double decimal_part = std::modf((to_d()), &int_part);

  return decimal_part;
}

long Rational::to_i() const {
  int result = p / q;
  return (sign) ? result : -result;
}

long Rational::to_l() const {
  long result = p / q;
  return (sign) ? result : -result;
}

double Rational::to_d() const {
  double result = (double)p / q;
  return (sign) ? result : -result;
}

long double Rational::to_ld() const {
  long double result = (long double)p / q;
  return (sign) ? result : -result;
}

float Rational::to_f() const {
  float result = (float)p / q;
  return (sign) ? result : -result;
}

std::string Rational::to_s() const {
  return (((sign) ? "" : "-") + std::to_string(p) + "/" + std::to_string(q));
}

Rational Rational::inverse() const {
  Rational result;

  result.p = this->q;
  result.q = this->p;
  result.sign = this->sign;

  return result;
}

Rational &Rational::operator=(const Rational &other) {
  if (this != &other) {
    this->sign = other.sign;
    this->p = other.p;
    this->q = other.q;
  }
  return *this;
}

Rational Rational::operator+(const Rational &other) const {
  Rational result;
  if (same_sign(other)) {
    result.sign = sign;
    result.q = q * other.q;
    result.p = (other.q * p) + (q * other.p);
    result.simplify();
    return result;
  }

  result.q = q * other.q;
  unsigned long n_1 = other.q * p;
  unsigned long n_2 = q * other.p;

  if (*this >= 0) {
    if (n_1 > n_2) {
      result.sign = true;
      result.p = n_1 - n_2;
    } else {
      result.sign = false;
      result.p = n_2 - n_1;
    }

  } else {
    if (n_1 > n_2) {
      result.sign = false;
      result.p = n_1 - n_2;
    } else {
      result.sign = true;
      result.p = n_2 - n_1;
    }
  }

  result.simplify();
  return result;
}

Rational Rational::operator-(const Rational &other) const {
  return (*this + (other * -1));
}

Rational Rational::operator*(const Rational &other) const {
  Rational result;

  result.sign = (sign == other.sign);
  result.p = p * other.p;
  result.q = q * other.q;

  result.simplify();
  return result;
}

Rational Rational::operator/(const Rational &other) const {
  return (*this * (other.inverse()));
}

bool Rational::operator>(const Rational &other) const {
  return (this->to_ld() > other.to_ld());
}

bool Rational::operator>=(const Rational &other) const {
  return (this->to_ld() >= other.to_ld());
}

bool Rational::operator<(const Rational &other) const {
  return (this->to_ld() < other.to_ld());
}

bool Rational::operator<=(const Rational &other) const {
  return (this->to_ld() <= other.to_ld());
}

bool Rational::operator==(const Rational &other) const {
  return (sign == other.sign) && (p == other.p) && (q == other.q);
}

bool Rational::operator!=(const Rational &other) const {
  return !(*this == other);
}

// private

void Rational::check_is_valid() const {
  if (this->q == 0)
    throw std::runtime_error("division by zero error");
}

bool Rational::same_sign(const Rational&other) const {
  return (sign == other.sign);
}

void Rational::simplify() {
  long mdc = mdc_euc(p, q);
  if (mdc == q) {
    p = p / q;
    q = 1;
    return;
  }
  if (mdc == 1)
    return;

  p /= mdc;
  q /= mdc;
}

void Rational::decimal_to_pq(double n) {
  Rational result = cont_fraction(n);
  (*this) = result;
}

// aux

Rational operator+(long l, const Rational &r) { return (Rational(l) + r); }
Rational operator+(const Rational &r, long l) { return (l + r); }

Rational operator+(int i, const Rational &r) { return (Rational(i) + r); }
Rational operator+(const Rational &r, int i) { return (i + r); }

Rational operator+(double d, const Rational &r) { return (Rational(d) + r); }
Rational operator+(const Rational &r, double d) { return (d + r); }

Rational operator-(long l, const Rational &r) { return (Rational(l) - r); }
Rational operator-(const Rational &r, long l) { return (r - Rational(l)); }

Rational operator-(int i, const Rational &r) { return (Rational(i) - r); }
Rational operator-(const Rational &r, int i) { return (r - Rational(i)); }

Rational operator-(double d, const Rational &r) { return (Rational(d) - r); }
Rational operator-(const Rational &r, double d) { return (r - Rational(d)); }

Rational operator*(long l, const Rational &r) { return (Rational(l) * r); }
Rational operator*(const Rational &r, long l) { return (Rational(l) * r); }

Rational operator*(int i, const Rational &r) { return (Rational(i) * r); }
Rational operator*(const Rational &r, int i) { return (Rational(i) * r); }

Rational operator*(double d, const Rational &r) { return (Rational(d) * r); }
Rational operator*(const Rational &r, double d) { return (Rational(d) * r); }

Rational operator/(long l, const Rational &r) { return (Rational(l) / r); }
Rational operator/(const Rational &r, long l) { return (r / Rational(l)); }

Rational operator/(int i, const Rational &r) { return (Rational(i) / r); }
Rational operator/(const Rational &r, int i) { return (r / Rational(i)); }

Rational operator/(double d, const Rational &r) { return (Rational(d) / r); }
Rational operator/(const Rational &r, double d) { return (r / Rational(d)); }

bool operator>(const Rational &r, long l) {
  return (r.to_l() > l || (r.to_l() == l && r.decimal() != 0));
}
bool operator>(long l, const Rational &r) { return (l > r.to_l()); }

bool operator>(const Rational &r, int i) { return (r > (long)i); }
bool operator>(int i, const Rational &r) { return ((long)i > r); }

bool operator>(const Rational &r, double d) { return (r.to_d() > d); }
bool operator>(double d, const Rational &r) { return (d > r.to_d()); }

bool operator>=(const Rational &r, int i) { return (r.to_l() >= i); }
bool operator>=(int i, const Rational &r) { return (i > r.to_l() || i == r); }

bool operator>=(const Rational &r, long l) { return (r.to_l() >= l); }
bool operator>=(long l, const Rational &r) { return (l > r.to_l() || l == r); }

bool operator>=(const Rational &r, double d) { return (r.to_d() >= d); }
bool operator>=(double d, const Rational &r) { return (d >= r.to_d()); }

bool operator<(const Rational &r, long l) { return (r.to_l() < l); }
bool operator<(long l, const Rational &r) {
  return ((l < r.to_l()) || (l == r.to_l() && r.decimal() != 0));
}
bool operator<(const Rational &r, int i) { return (r < (long)i); }
bool operator<(int i, const Rational &r) { return ((long)i < r); }

bool operator<(const Rational &r, double d) { return (r.to_d() < d); }
bool operator<(double d, const Rational &r) { return (d < r.to_d()); }

bool operator<=(const Rational &r, long l) { return (r.to_l() < l || r == l); }
bool operator<=(long l, const Rational &r) { return (l < r.to_l() || l == r); }

bool operator<=(const Rational &r, int i) { return (r <= (long)i); }
bool operator<=(int i, const Rational &r) { return ((long)i <= r); }

bool operator<=(const Rational &r, double d) { return (r.to_d() <= d); }
bool operator<=(double d, const Rational &r) { return (d <= r.to_d()); }

bool operator==(const Rational &r, long l) {
  return (r.to_l() == l && r.decimal() == 0);
}
bool operator==(long l, const Rational &r) { return (r == l); }

bool operator==(const Rational &r, int i) { return (r == (long)i); }
bool operator==(int i, const Rational &r) { return ((long)i == r); }

bool operator==(const Rational &r, double d) { return (r.to_d() == d); }
bool operator==(double d, const Rational &r) { return (r == d); }

long mdc_euc(long a, long b) {
  while (b != 0) {
    long rest = a % b;
    a = b;
    b = rest;
  }
  return a;
}

Rational cont_fraction(double n) {
  double int_part;
  double decimal_part = std::modf(n, &int_part);

  if (decimal_part == 0)
    return Rational((long)int_part, (long)1);

  Rational result = ((long)int_part + (1 / decimal_part));
  return result;
}
