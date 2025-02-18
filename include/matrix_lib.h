#ifndef MATRIX_LIB_H_
#define MATRIX_LIB_H_

#include <math.h>
#include <sstream>
#include <string>
#include <vector>

// TODO: add template support
class Matrix {
public:
  Matrix(unsigned rows, unsigned columns);
  Matrix(const Matrix &other);
  ~Matrix();

  void set_elements(const float *el); // TODO
  void set_elements(const std::vector<float>);
  void set_elements_stdin(); // TODO
  void update_el(unsigned row, unsigned column, float new_el);
  float at(unsigned row, unsigned column) const;

  unsigned row_size() const;
  unsigned column_size() const;

  bool is_identity() const;
  bool is_square() const;
  bool is_null() const;
  bool is_column() const;
  bool is_row() const;
  bool is_diagonal() const;
  bool is_upper_tri() const;
  bool is_lower_tri() const;
  bool is_symmetric() const;
  bool is_antisymmetric() const;
  bool is_scalar() const;

  Matrix transpose() const;
  double stroke() const;
  double det() const; // TODO
  double minor_comp(unsigned, unsigned) const;
  double cofactor(unsigned, unsigned) const;

  Matrix &operator=(const Matrix &other);
  Matrix operator+(const Matrix &other) const;
  Matrix operator-(const Matrix &other) const;
  Matrix operator*(const float scalar) const;
  Matrix operator*(const Matrix &other) const;
  bool operator==(const Matrix &other) const;

  std::stringstream print() const;
  std::stringstream print_class() const;
  std::stringstream describe() const; // TODO

private:
  unsigned rows;
  unsigned columns;
  float **mtr;

  void init_mtr();
  void clear_mtr();
  void copy_elements_to(Matrix &) const;

  double det_order_2() const;
  double det_order_3() const;
  double det_order_n() const;

  bool vector_can_fill_mtr(const std::vector<float>) const;
  void check_mtr() const;
  bool is_valid_position(unsigned row, unsigned column) const;
  bool same_size_as(const Matrix&) const;
  bool has_zero_line() const;
  Matrix gen_compl_mtr(unsigned suppr_r, unsigned suppr_c) const;
};

#endif
