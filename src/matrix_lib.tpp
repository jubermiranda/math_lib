#ifndef MATRIX_LIB_TPP_
#define MATRIX_LIB_TPP_

#include <cstddef>

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns) : rows(rows), columns(columns) {
  this->init_mtr();
}

template <typename T> Matrix<T>::Matrix() : rows(0), columns(0), mtr(nullptr) {}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &other)
    : rows(other.rows), columns(other.columns) {

  this->init_mtr();
  other.copy_elements_to(*this);
}

template <typename T> Matrix<T>::~Matrix() { this->clear_mtr(); }

template <typename T> void Matrix<T>::set_elements(const std::vector<T> &vec) {
  if (!vector_can_fill_mtr(vec))
    throw std::runtime_error("bad vector size. cannot fill mtr");
  if (vec.size() > 0)
    this->throw_if_null();

  for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < this->columns; j++)
      this->mtr[i][j] = vec.at((i * columns + j));
}

template <typename T> const T &Matrix<T>::at(size_t row, size_t column) const {
  if (!is_valid_position(row, column))
    throw std::runtime_error("index out of range");

  return this->mtr[row][column];
}

template <typename T> T &Matrix<T>::at(size_t row, size_t column) {
  if (!is_valid_position(row, column))
    throw std::runtime_error("index out of range");

  return this->mtr[row][column];
}

template <typename T> size_t Matrix<T>::row_size() const {
  return this->rows; //
}
template <typename T> size_t Matrix<T>::column_size() const {
  return this->columns;
}

template <typename T> bool Matrix<T>::is_identity(const Matrix<T> &m) {
  if (!Matrix<T>::is_square(m))
    return false;

  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < m.columns; j++)
      if (m.mtr[i][j] != ((i == j) ? 1 : 0))
        return false;
  }

  return true;
}

template <typename T> bool Matrix<T>::is_square(const Matrix<T> &m) {
  return (m.rows == m.columns);
}

template <typename T> bool Matrix<T>::is_null(const Matrix<T> &m) {
  for (int i = 0; i < m.rows; i++)
    for (int j = 0; j < m.columns; j++)
      if (m.mtr[i][j] != 0)
        return false;

  return true;
}

template <typename T> bool Matrix<T>::is_column(const Matrix<T> &m) {
  return (m.columns == 1);
}

template <typename T> bool Matrix<T>::is_row(const Matrix<T> &m) {
  return (m.rows == 1);
}

template <typename T> bool Matrix<T>::is_diagonal(const Matrix<T> &m) {
  if (!Matrix<T>::is_square(m))
    return false;

  for (int i = 0; i < m.rows; i++)
    for (int j = 0; j < m.columns; j++)
      if (i != j && m.mtr[i][j] != 0)
        return false;

  return true;
}

template <typename T> bool Matrix<T>::is_upper_tri(const Matrix<T> &m) {
  if (!Matrix<T>::is_square(m))
    return false;

  for (int i = 0; i < m.rows; i++)
    for (int j = 0; j < i; j++)
      if (m.mtr[i][j] != 0)
        return false;

  return true;
}

template <typename T> bool Matrix<T>::is_lower_tri(const Matrix<T> &m) {
  if (!Matrix<T>::is_square(m))
    return false;

  for (int i = 0; i < m.rows; i++)
    for (int j = i + 1; j < m.columns; j++)
      if (m.mtr[i][j] != 0)
        return false;

  return true;
}

template <typename T> bool Matrix<T>::is_symmetric(const Matrix<T> &m) {
  if (!Matrix<T>::is_square(m))
    return false;

  for (int i = 0; i < m.rows; i++)
    for (int j = i; j < m.columns; j++)
      if (m.mtr[i][j] != m.mtr[j][i])
        return false;

  return true;
}

template <typename T> bool Matrix<T>::is_antisymmetric(const Matrix<T> &m) {
  if (!Matrix<T>::is_square(m))
    return false;

  for (int i = 0; i < m.rows; i++)
    if (m.mtr[i][i] != 0)
      return false;
  return true;
}

template <typename T> bool Matrix<T>::is_scalar(const Matrix<T> &m) {
  if (!Matrix<T>::is_diagonal(m))
    return false;

  T diagonal_el = m.mtr[0][0];
  for (int i = 1; i < m.rows; i++)
    if (m.mtr[i][i] != diagonal_el)
      return false;

  return true;
}

template <typename T> Matrix<T> Matrix<T>::transpose() const {
  Matrix<T> result = Matrix<T>(this->rows, this->columns);
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->columns; j++) {
      result.at(i, j) = this->at(j, i);
    }
  }

  return result;
}

template <typename T> T Matrix<T>::stroke() const {
  if (!Matrix<T>::is_square(*this))
    throw std::runtime_error(
        "Cannot calculate the stroke of a non-square matrix");

  T sum = 0;
  for (int i = 0; i < this->rows; i++)
    sum += this->mtr[i][i];

  return sum;
}

template <typename T> T Matrix<T>::det() const {
  if (!Matrix<T>::is_square(this))
    throw std::runtime_error(
        "Cannot calculate the determinant of a non-square matrix");

  switch (this->rows) {

  case 1:
    return this->at(0, 0);
    break;

  case 2:
    return this->det_order_2();
    break;

  case 3:
    return this->det_order_3();
    break;

  default:
    return this->det_order_n();
  }

  return 0;
}

template <typename T> T Matrix<T>::minor_comp(size_t row, size_t column) const {
  if (this->rows <= 1 || this->columns <= 1)
    throw std::runtime_error("to calc minor_comp, mtr order should be > 1");

  if (!is_valid_position(row, column))
    throw std::runtime_error("index out of range");

  // TODO: Optimize memory usage by performing the calculation
  // directly on the object instead of creating a new one.
  Matrix<T> aux = this->gen_compl_mtr(row, column);
  return aux.det();
}

template <typename T> T Matrix<T>::cofactor(size_t line, size_t column) const {
  return (this->minor_comp(line, column) *
          (((line + column) % 2 == 0) ? 1 : -1));
}

template <typename T> Matrix<T> &Matrix<T>::operator=(const Matrix<T> &other) {
  if (this != &other)
    other.copy_elements_to(*this);
  return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) const {
  if (!Matrix::same_order(*this, other))
    throw std::runtime_error("cannot sum matrix of difeerent order");

  Matrix<T> result = Matrix<T>(this->rows, this->columns);
  for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < this->columns; j++)
      result.at(i, j) = this->at(i, j) + other.at(i, j);

  return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &other) const {
  if (!Matrix::same_order(*this, other))
    throw std::runtime_error("cannot diff matrix of difeerent order");

  Matrix<T> result = Matrix<T>(this->rows, this->columns);
  for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < this->columns; j++)
      result.at(i, j) = this->at(i, j) - other.at(i, j);

  return result;
}

template <typename T> Matrix<T> Matrix<T>::operator*(double scalar) const {

  Matrix<T> result = Matrix<T>(this->rows, this->columns);
  for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < this->columns; j++)
      result.at(i, j) = this->at(i, j) * scalar;

  return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const {
  if (this->columns != other.rows)
    throw std::runtime_error(
        "Cannot multiply matrices: incompatible dimensions. "
        "Expected A(m x n) and B(n x o).");

  Matrix<T> result = Matrix(this->rows, other.columns);

  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < other.columns; j++) {

      T sum = 0;
      for (int k = 0; k < this->columns; k++)
        sum += this->mtr[i][k] * other.mtr[k][j];
      result.at(i, j) = sum;
    }
  }

  return result;
}

template <typename T> bool Matrix<T>::operator==(const Matrix<T> &other) const {
  if (!Matrix::same_order(*this, other))
    return false;

  for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < this->columns; j++)
      if (this->mtr[i][j] != other.mtr[i][j])
        return false;

  return true;
}

template <typename T> bool Matrix<T>::operator!=(const Matrix<T> &other) const {
  return !(this->operator==(other));
}

// --- private

template <typename T> void Matrix<T>::init_mtr() {
  if (this->rows > 0 && this->columns > 0) {
    this->mtr = new T *[rows];
    for (int i = 0; i < this->rows; i++) {
      this->mtr[i] = new T[columns];
    }
  } else {
    this->mtr = nullptr;
  }
}

template <typename T> void Matrix<T>::clear_mtr() {
  if (this->mtr != nullptr) {
    for (int i = 0; i < this->rows; i++)
      if (this->mtr[i] != nullptr)
        delete[](this->mtr[i]);
    delete[](this->mtr);
  }
}

template <typename T> void Matrix<T>::copy_elements_to(Matrix<T> &other) const {
  other.throw_if_null();
  if (!(Matrix::same_order(*this, other))) {
    this->clear_mtr();
    this->rows = other.rows;
    this->columns = other.columns;
    this->init_mtr();
  }

  for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < this->columns; j++)
      other.mtr[i][j] = this->mtr[i][j];
}

template <typename T> T Matrix<T>::det_order_2() const {
  if (this->rows != 2 || this->columns != 2)
    throw std::runtime_error("invalid matrix dimentions");

  return ((this->mtr[0][0] * this->mtr[1][1]) -
          (this->mtr[0][1] * this->mtr[1][0]));
}

template <typename T> T Matrix<T>::det_order_3() const {
  T main_diagonal = 0;
  main_diagonal += this->mtr[0][0] * this->mtr[1][1] * this->mtr[2][2];
  main_diagonal += this->mtr[0][1] * this->mtr[1][2] * this->mtr[2][0];
  main_diagonal += this->mtr[0][2] * this->mtr[1][0] * this->mtr[2][1];

  T sec_diagonal = 0;
  sec_diagonal += mtr[2][0] * mtr[1][1] * mtr[0][2];
  sec_diagonal += mtr[2][1] * mtr[1][2] * mtr[0][0];
  sec_diagonal += mtr[2][2] * mtr[1][0] * mtr[0][1];

  return main_diagonal - sec_diagonal;
}

template <typename T> T Matrix<T>::det_order_n() const {
  if (this->rows <= 3 || this->columns <= 3)
    throw std::runtime_error("expected dimentions > 3");
  if (!Matrix::is_square(*this))
    throw std::runtime_error("matrix not square. cannot calc det");

  size_t n = this->rows;

  // If a matrix has an entire line equals to 0
  // then the determinant is 0
  // if (has_zero_line())
  //   return 0;

  T result = 0;
  for (int i = 0; i < n; i++) {
    result += (this->mtr[0][i] * this->cofactor(0, i));
  }

  return result;
}

template <typename T>
bool Matrix<T>::vector_can_fill_mtr(const std::vector<T> &vec) const {
  return (vec.size() == this->rows * this->columns);
}

template <typename T> void Matrix<T>::throw_if_null() const {
  if(this->rows > 0 && this->columns > 0)
    if (this->mtr == nullptr)
      throw std::runtime_error("null matrix exception");
}

template <typename T>
bool Matrix<T>::is_valid_position(size_t row, size_t column) const {
  return ((row < this->rows) && (column < this->columns));
}

template <typename T>
bool Matrix<T>::same_order(const Matrix<T> &m1, const Matrix<T> &m2) {
  return (m1.rows == m2.rows && m1.columns == m2.columns);
}

template <typename T> bool Matrix<T>::has_line_equals_zero() const {
  if (!Matrix::is_square(*this))
    throw std::runtime_error("mtr not square");

  size_t n = this->rows;

  for (int i = 0; i < n; i++) {
    // chekc columns
    if (mtr[0][i] == 0) {
      bool all_zero = true;
      for (int j = 1; j < n; j++) {
        if (mtr[j][i] != 0) {
          all_zero = false;
          break;
        }
      }
      if (all_zero)
        return true;
    }
    // chekc rows
    if (mtr[i][0] == 0) {
      bool all_zero = true;
      for (int j = 1; j < n; j++) {
        if (mtr[i][j] != 0) {
          all_zero = false;
          break;
        }
      }
      if (all_zero)
        return true;
    }
  }

  return false;
}

template <typename T>
Matrix<T> Matrix<T>::gen_compl_mtr(size_t suppr_r, size_t suppr_c) const {

  Matrix<T> aux(this->rows - 1, this->columns - 1);
  for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < this->columns; j++)
      if (i != suppr_r && j != suppr_c)
        aux.at(((i < suppr_r) ? i : i - 1), ((j < suppr_c) ? j : j - 1)) =
            this->mtr[i][j];
  return aux;
}

#endif /* ifndef MATRIX_LIB_TPP_  */
