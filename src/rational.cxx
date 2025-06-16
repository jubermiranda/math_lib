#include "rational.h"
#include <cmath>
#include <numbers>
#include <stdexcept>
#include <string>
#include <vector>

using std::vector;

const unsigned STD_CONT_FRA_MAX = 19;
const double kTolerance = 1e-13;

long mdc_euc(long a, long b);
bool near_zero(double n);

Rational::Rational() : p(0), q(1), sign(true){};

Rational::Rational(const Rational &other)
    : p(other.p), q(other.q), sign(other.sign){};

Rational::Rational(long p, long q) { init_attr(p, q); }

Rational::Rational(long p, const Rational &q) {
  if (q == (long)0)
    throw std::runtime_error("division by 0 not allowed");

  if (p == 0) {
    *this = Rational();
    return;
  }

  this->sign = ((p >= 0) == q.sign);
  this->q = q.p;
  this->p = p * q.q;
  simplify();
}

Rational::Rational(const Rational &p, const Rational &q) {
  this->sign = (p.sign == q.sign);
  this->p = p.p * q.q;
  this->q = p.q * q.p;
  simplify();
}

Rational::Rational(long n) {
  this->sign = (n >= 0);
  p = (n >= 0) ? n : -n;
  q = 1;
}

Rational::Rational(int n) { (*this) = Rational((long)n); }

Rational::Rational(double n) { *this = double_to_rational(n); }

long Rational::numerator() const { return p; }

long Rational::denominator() const { return q; }

double Rational::decimal() const {
  double int_part;
  double decimal_part = std::modf(static_cast<double>(*this), &int_part);

  return decimal_part;
}

Rational::operator long() const {
  long result = p / q;
  return (sign) ? result : -result;
}

Rational::operator unsigned long() const { return (unsigned long)(p / q); }

Rational::operator double() const {
  double result = (double)p / q;
  return (sign) ? result : -result;
}

std::string Rational::to_s() const {
  if(this->p == 0)
    return std::string("0");

  return (((sign) ? "" : "-") + std::to_string(p) + "/" + std::to_string(q));
}

Rational Rational::inverse() const {
  if (numerator() == 0)
    return (Rational());

  Rational result;

  result.p = this->q;
  result.q = this->p;
  result.sign = this->sign;
  result.simplify();

  return result;
}

void Rational::update_denominator(const Rational &r) {
  if (r == (long)0)
    throw std::runtime_error("division by 0 not allowed");
  if (p == 0)
    return;

  sign = (sign == r.sign);
  q = r.p;
  p = p * r.q;
  this->simplify();
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
  return (static_cast<double>(*this) > static_cast<double>(other));
}

bool Rational::operator>=(const Rational &other) const {
  return (this->operator>(other) || this->operator==(other));
}

bool Rational::operator<(const Rational &other) const {
  return (static_cast<double>(*this) < static_cast<double>(other));
}

bool Rational::operator<=(const Rational &other) const {
  return (this->operator<(other) || this->operator==(other));
}

bool Rational::operator==(const Rational &other) const {
  return (sign == other.sign) && (p == other.p) && (q == other.q);
}

bool Rational::operator!=(const Rational &other) const {
  return !(this->operator==(other));
}

// private

void Rational::init_attr(long p, long q) {
  this->sign = (p >= 0?(q>=0?1:0):(q<0?1:0));
  this->p = (p >= 0) ? p : p * -1;
  this->q = (q >= 0) ? q : q * -1;
  check_is_valid();
  simplify();
}

void Rational::check_is_valid() const {
  if (this->q == 0)
    throw std::runtime_error("denominator cannot be 0");
}

bool Rational::same_sign(const Rational &other) const {
  return (sign == other.sign);
}

void Rational::simplify() {
  if (p == 0){
    sign = true;
    q = 1;
    return;
  }

  if( p == q ){
    p = 1;
    q = 1;
    return;
  }

  long mdc = mdc_euc(p, q);
  if (mdc == 1)
    return;

  p /= mdc;
  q /= mdc;
}

Rational Rational::double_to_rational(double n) const {
  long p, q = 1;
  while( n != std::floor(n)){
    n *= 10;
    q *= 10;
  }
  p = n;
  Rational r =  Rational(p, q);
  return r;
}

Rational operator+(double d, const Rational &r) { return (Rational(d) + r); }
Rational operator+(const Rational &r, double d) { return (d + r); }

Rational operator-(double d, const Rational &r) { return (Rational(d) - r); }
Rational operator-(const Rational &r, double d) { return (r - Rational(d)); }

Rational operator*(double d, const Rational &r) { return (Rational(d) * r); }
Rational operator*(const Rational &r, double d) { return (Rational(d) * r); }

Rational operator/(double d, const Rational &r) { return (Rational(d) / r); }
Rational operator/(const Rational &r, double d) { return (r / Rational(d)); }

bool operator>(const Rational &r, double d) {
  return (static_cast<double>(r) > d);
}
bool operator>(double d, const Rational &r) {
  return (d > static_cast<double>(r));
}

bool operator>=(const Rational &r, double d) {
  return (static_cast<double>(r) >= d);
}
bool operator>=(double d, const Rational &r) {
  return (d >= static_cast<double>(r));
}

bool operator<(const Rational &r, double d) {
  return (static_cast<double>(r) < d);
}
bool operator<(double d, const Rational &r) {
  return (d < static_cast<double>(r));
}

bool operator<=(const Rational &r, double d) {
  return (static_cast<double>(r) <= d);
}
bool operator<=(double d, const Rational &r) {
  return (d <= static_cast<double>(r));
}

bool operator==(const Rational &r, double d) {
  return (static_cast<double>(r) == d);
}
bool operator==(double d, const Rational &r) { return (r == d); }

bool operator!=(const Rational &r, double d) { return !(r == d); }
bool operator!=(double d, const Rational &r) { return r != d; }

long mdc_euc(long a, long b) {
  while (b != 0) {
    long rest = a % b;
    a = b;
    b = rest;
  }
  return a;
}

bool near_zero(double n) {
  return (0.0 - kTolerance <= n && 0.0 + kTolerance >= n);
}

Rational double_to_r_continuous_fraction(double n){
  double a0;
  double decimal_part;
  decimal_part = std::modf(n, &a0);
  Rational result((long)a0);
  if (near_zero(decimal_part))
    return result;

  double an;
  decimal_part = 1.0 / decimal_part;
  decimal_part = std::modf(decimal_part, &an);
  if (near_zero(decimal_part))
    return (result + Rational(1, (long)an));

  vector<double> parts = vector<double>();
  parts.push_back(an);

  while (!near_zero(decimal_part) && parts.size() < STD_CONT_FRA_MAX - 1) {
    decimal_part = 1 / decimal_part;
    decimal_part = std::modf(decimal_part, &an);
    parts.push_back(an);
  }

  Rational aux((long)(parts.at(parts.size() - 1)));
  for (int i = parts.size() - 2; i >= 0; i--) {
    aux = parts.at(i) + Rational(1, aux);
  }
  result = result + Rational(1, aux);
  return result;
}
