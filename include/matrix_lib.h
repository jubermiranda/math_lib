#ifndef MATRIX_LIB_H_
#define MATRIX_LIB_H_

#include <math.h>
#include <sstream>
#include <string>

class Matrix {
public:
  Matrix(unsigned lines,unsigned columns);
  ~Matrix();

  void set_elements(const int *el);
  void set_elements_stdin();
  void update_el(unsigned line, unsigned column, int new_el);

  unsigned get_lines() const;
  unsigned get_columns() const;
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

private:
  int lines;
  int columns;
  std::string classification;
  int **mtr;

  void init_mtr();
};

#endif
