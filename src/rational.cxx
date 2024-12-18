#include "rational.h"
#include <cmath>
#include <numbers>
#include <stdexcept>

void decimal_to_pq(const double& n, long&, long&);

Rational::Rational() : p(0), q(1), sign(false){};

Rational::Rational(long p, long q) : p(p), q(q), sign((p*q > 0)){}
Rational::Rational(int p, int q) : p(p), q(q), sign((p*q > 0)){}
Rational::Rational(unsigned p, unsigned q) : p(p), q(q), sign(false){}

Rational::Rational(double n) {
  try{
    long p, q;
    decimal_to_pq(n, p, q);

  } catch (const std::runtime_error& e){
    //TODO
    p = 0;
    q = 1;
    throw e;
  }
}

void decimal_to_pq(const double& n, long& p, long& q){

}
