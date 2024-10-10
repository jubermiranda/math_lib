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

  void set_elements(const float *el); // TODO
  void set_elements(const std::vector<float>);
  void set_elements_stdin(); // TODO
  void update_el(unsigned line, unsigned column, float new_el);
  float at(unsigned line, unsigned column) const;

  unsigned line_size() const;
  unsigned column_size() const;

  bool is_identity() const;
  bool is_square() const;
  bool is_null() const;
  bool is_column() const;
  bool is_line() const;
  bool is_diagonal() const;
  bool is_upper_tri() const;
  bool is_lower_tri() const;
  bool is_symmetric() const;
  bool is_antisymmetric() const;
  bool is_scalar() const;

  Matrix transpose() const;
  float stroke() const;
  double det() const; // TODO
  double minor_comp(unsigned, unsigned) const;
  double cofactor(unsigned, unsigned) const;

  Matrix &operator=(const Matrix &other);
  Matrix operator+(const Matrix &other) const;
  Matrix operator-(const Matrix &other) const;
  Matrix operator*(const Matrix &other) const;
  Matrix operator*(const float scalar) const;
  bool operator==(const Matrix &other) const;

  std::stringstream describe() const; // TODO
  std::stringstream print() const;
  std::stringstream print_class() const;

private:
  unsigned lines;
  unsigned columns;
  float **mtr;

  void init_mtr();
  void clear_mtr();

  double det_order_2() const;
  double det_order_3() const;
  double det_order_n() const;
};

#endif
