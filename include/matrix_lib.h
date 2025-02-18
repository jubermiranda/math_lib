#ifndef MATRIX_LIB_H_
#define MATRIX_LIB_H_

#include <math.h>
#include <sstream>
#include <string>
#include <vector>

template <typename T> class Matrix {
public:
  Matrix(size_t rows, size_t columns);
  Matrix(const Matrix<T> &other);
  ~Matrix();

  void set_elements(const std::vector<T>);
  const T &at(size_t row, size_t column) const;
  T &at(size_t row, size_t column);

  size_t row_size() const;
  size_t column_size() const;

  Matrix<T> transpose() const;
  T stroke() const;
  T det() const;
  T minor_comp(size_t, size_t) const;
  T cofactor(size_t, size_t) const;

  Matrix<T> &operator=(const Matrix<T> &other);
  Matrix<T> operator+(const Matrix<T> &other) const;
  Matrix<T> operator-(const Matrix<T> &other) const;
  Matrix<T> operator*(const double scalar) const;
  Matrix<T> operator*(const Matrix<T> &other) const;
  Matrix<T> operator^(int) const;

  bool operator==(const Matrix<T> &other) const;
  bool operator!=(const Matrix<T> &other) const;

  std::stringstream print() const;
  std::stringstream print_classes() const;
  std::string to_s() const; // TODO

  static bool is_identity(const Matrix<T> &);
  static bool is_square(const Matrix<T> &);
  static bool is_null(const Matrix<T> &);
  static bool is_column(const Matrix<T> &);
  static bool is_row(const Matrix<T> &);
  static bool is_diagonal(const Matrix<T> &);
  static bool is_upper_tri(const Matrix<T> &);
  static bool is_lower_tri(const Matrix<T> &);
  static bool is_symmetric(const Matrix<T> &);
  static bool is_antisymmetric(const Matrix<T> &);
  static bool is_scalar(const Matrix<T> &);
  static bool same_order(const Matrix<T> &, const Matrix<T> &);

private:
  size_t rows;
  size_t columns;
  T **mtr;

  void init_mtr();
  void clear_mtr();
  void copy_elements_to(Matrix<T> &) const;

  double det_order_2() const;
  double det_order_3() const;
  double det_order_n() const;

  bool vector_can_fill_mtr(const std::vector<T>) const;
  void throw_if_null() const;
  bool is_valid_position(size_t row, size_t column) const;
  bool has_line_equals_zero() const;
  Matrix<T> gen_compl_mtr(size_t suppr_r, size_t suppr_c) const;
};

#endif
