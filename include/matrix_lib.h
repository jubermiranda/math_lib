#ifndef MATRIX_LIB_H_
#define MATRIX_LIB_H_

#include <math.h>
#include <sstream>
#include <string>
#include <vector>

class Matrix {
public:
  Matrix(unsigned lines,unsigned columns);
  ~Matrix();

  void set_elements(const int *el);//TODO
  void set_elements(const std::vector<int>);
  void set_elements_stdin();//TODO
  void update_el(unsigned line, unsigned column, int new_el);//TODO

  unsigned get_lines() const;
  unsigned get_columns() const;
  std::stringstream describe() const;//TODO
  std::stringstream print() const;//TODO
  std::stringstream print_class() const;//TODO
  Matrix tr() const;//TODO
  int stroke() const;//TODO
  long det() const;//TODO

  Matrix operator+(const Matrix& other);//TODO
  Matrix operator-(const Matrix& other);//TODO
  Matrix operator*(const Matrix& other);//TODO
  Matrix operator*(const int scalar);//TODO

private:
  int lines;
  int columns;
  std::string classification;
  int **mtr;

  void init_mtr();
};

#endif
