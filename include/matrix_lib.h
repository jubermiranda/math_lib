#ifndef MATRIX_LIB_H_
#define MATRIX_LIB_H_

#include <math.h>
#include <sstream>
#include <string>
#include <vector>

class Matrix {
public:
  Matrix(unsigned lines, unsigned columns);
  Matrix(const Matrix &other);
  ~Matrix();

  void set_elements(const int *el); // TODO
  void set_elements(const std::vector<int>);
  void set_elements_stdin(); // TODO
  void update_el(unsigned line, unsigned column, int new_el);
  int at(unsigned line, unsigned column) const;

  unsigned get_lines() const;
  unsigned get_columns() const;
  bool is_identity() const;
  bool is_square() const;
  bool is_null() const;
  bool is_column() const;
  bool is_line() const;
  bool is_diagonal() const;
  bool is_upper_tri() const;
  bool is_lower_tri() const;
  bool is_symmetric() const;

  std::stringstream describe() const; // TODO
  std::stringstream print() const;
  std::stringstream print_class() const;

  Matrix transpose() const;
  int stroke() const;
  long det() const; // TODO

  Matrix &operator=(const Matrix &other);
  Matrix operator+(const Matrix &other) const;
  Matrix operator-(const Matrix &other) const;
  Matrix operator*(const Matrix &other) const;
  Matrix operator*(const int scalar) const;
  bool operator==(const Matrix &other) const;

private:
  int lines;
  int columns;
  int **mtr;

  void init_mtr();
  void clear_mtr();
};

#endif
