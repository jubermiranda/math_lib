#include "rational.h"
#include <cmath>
#include <numbers>
#include <stdexcept>
#include <string>

void decimal_to_pq(const double& n, long&, long&);
long mdc_euc(long a, long b);

Rational::Rational() : p(0), q(1), sign(true){};

Rational::Rational(long p, long q) : p(p), q(q), sign((p*q >= 0)){
  check_is_valid();
  simplify();
}

Rational::Rational(int p, int q) : p(p), q(q), sign((p*q >= 0)){
  check_is_valid();
  simplify();
}

Rational::Rational(unsigned p, unsigned q) : p(p), q(q), sign(true){
  check_is_valid();
  simplify();
}

Rational::Rational(double n) {
  long p, q;
  decimal_to_pq(n, p, q);
  this->p = p;
  this->q = q;
  this->sign = (p*q >= 0);
}

Rational::Rational(float n) {
  long p, q;
  decimal_to_pq(n, p, q);
  this->p = p;
  this->q = q;
  this->sign = (p*q >= 0);
}

long Rational::to_l() const {
  return (long) (this->p / this->q);
}


double Rational::to_d() const {
  return  ((double)this->p / (double)this->q);
}

float Rational::to_f() const {
  return  (float)((float)this->p / (float)this->q);
}

std::string Rational::to_s() const {
  return (std::to_string(p) + "/" + std::to_string(q));
}

void decimal_to_pq(const double& n, long& p, long& q){
  throw std::runtime_error("not implemented");
}

void Rational::check_is_valid() const {
  if(this->q == 0)
    throw std::runtime_error("division by zero error");
}

void Rational::simplify() {
  long mdc = mdc_euc(p, q);
  if(mdc == q){
    p = p/q;
    q = 1;
    return;
  }
  if(mdc == 1)
    return;

  p /= mdc;
  q /= mdc;
}

long mdc_euc(long a, long b){
  while(b != 0){
    long rest = a % b;
    a = b;
    b = rest;
  }
  return a;
}
