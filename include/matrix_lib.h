#ifndef MATRIX_LIB_H_
#define MATRIX_LIB_H_

#include <math.h>
#include <sstream>
#include <string>

class Matrix {
public:
  Matrix(int m,int n);

  void set_elements(const int *el);
  void set_elements_stdin();

  int lines() const;
  int columns() const;
  std::stringstream describe() const;
  std::stringstream print_el() const;
  std::stringstream print_class() const;
  Matrix tr() const;
  int stroke() const;
  long det() const;

  Matrix operator+(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator*(const Matrix& other);
  Matrix operator*(const int scalar);
};

#endif
