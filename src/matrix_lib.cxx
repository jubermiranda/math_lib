#include "matrix_lib.h"

using namespace std;

Matrix::Matrix(unsigned rows, unsigned columns) : rows(rows), columns(columns) {
  this->init_mtr();
}

Matrix::Matrix(const Matrix &other) : rows(other.rows), columns(other.columns) {

  this->init_mtr();
  other.copy_elements_to(*this);
}

Matrix::~Matrix() { this->clear_mtr(); }

void Matrix::set_elements(const vector<float> vec) {
  this->check_mtr();

  if (vector_can_fill_mtr(vec)) {

    for (int i = 0; i < this->rows; i++)
      for (int j = 0; j < this->columns; j++)
        this->mtr[i][j] = vec.at((i * columns + j));

  } else
    throw runtime_error("bad vector size. cannot fill mtr");
}

void Matrix::update_el(unsigned row, unsigned column, float new_el) {
  this->check_mtr();

  if (!is_valid_position(row, column))
    throw runtime_error("index out of range");

  this->mtr[row][column] = new_el;
}

float Matrix::at(unsigned row, unsigned column) const {
  if (!is_valid_position(row, column))
    throw runtime_error("index out of range");

  return this->mtr[row][column];
}

unsigned Matrix::row_size() const { return this->rows; }
unsigned Matrix::column_size() const { return this->columns; }

bool Matrix::is_identity() const {
  if (!this->is_square())
    return false;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++)
      if (mtr[i][j] != ((i == j) ? 1 : 0))
        return false;
  }

  return true;
}

bool Matrix::is_square() const { return (this->rows == this->columns); }

bool Matrix::is_null() const {
  for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < this->columns; j++)
      if (this->mtr[i][j] != 0)
        return false;

  return true;
}

bool Matrix::is_column() const { return (this->columns == 1); }

bool Matrix::is_row() const { return (this->rows == 1); }

bool Matrix::is_diagonal() const {
  if (!this->is_square())
    return false;

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++)
      if (i != j && this->mtr[i][j] != 0)
        return false;

  return true;
}

bool Matrix::is_upper_tri() const {
  if (!this->is_square())
    return false;

  for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < i; j++)
      if (this->mtr[i][j] != 0)
        return false;

  return true;
}

bool Matrix::is_lower_tri() const {
  if (!this->is_square())
    return false;

  for (int i = 0; i < this->rows; i++)
    for (int j = i + 1; j < this->columns; j++)
      if (this->mtr[i][j] != 0)
        return false;

  return true;
}

bool Matrix::is_symmetric() const {
  if (!this->is_square())
    return false;

  for (int i = 0; i < this->rows; i++)
    for (int j = i; j < this->columns; j++)
      if (this->mtr[i][j] != this->mtr[j][i])
        return false;

  return true;
}

bool Matrix::is_antisymmetric() const {
  if (!this->is_square())
    return false;

  for (int i = 0; i < this->rows; i++)
    if (this->mtr[i][i] != 0)
      return false;
  return true;
}

bool Matrix::is_scalar() const {
  if (!this->is_diagonal())
    return false;

  float diagonal_el = this->mtr[0][0];
  for (int i = 1; i < this->rows; i++)
    if (this->mtr[i][i] != diagonal_el)
      return false;

  return true;
}

Matrix Matrix::transpose() const {
  Matrix result = Matrix(this->rows, this->columns);
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->columns; j++) {
      result.update_el(i, j, this->at(j, i));
    }
  }

  return result;
}

double Matrix::stroke() const {
  if (!this->is_square())
    throw runtime_error("mtr not square");

  double sum = 0;
  for (int i = 0; i < this->rows; i++)
    sum += this->mtr[i][i];

  return sum;
}

double Matrix::det() const {
  if (!this->is_square())
    throw runtime_error("cannot calc det. matrix not square");

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

double Matrix::minor_comp(unsigned row, unsigned column) const {
  if (this->rows <= 1 || this->columns <= 1)
    throw runtime_error("to calc minor_comp, mtr order should be > 1");

  if (!is_valid_position(row, column))
    throw runtime_error("index out of range");

  Matrix aux(this->rows - 1, this->columns - 1);
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->columns; j++) {
      if (i != row && j != column) {
        aux.update_el(((i < row) ? i : i - 1), ((j < column) ? j : j - 1),
                      this->mtr[i][j]);
      }
    }
  }

  return aux.det();
}

double Matrix::cofactor(unsigned line, unsigned column) const {
  return (this->minor_comp(line, column) *
          (((line + column) % 2 == 0) ? 1 : -1));
}

Matrix &Matrix::operator=(const Matrix &other) {
  if (this != &other) {
    this->clear_mtr();

    this->rows = other.rows;
    this->columns = other.columns;
    this->init_mtr();
  }
  return *this;
}

Matrix Matrix::operator+(const Matrix &other) const {
  if (this->rows != other.rows || this->columns != other.columns)
    throw runtime_error("cannot sum matrix of difeerent order");

  Matrix result = Matrix(this->rows, this->columns);
  for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < this->columns; j++)
      result.update_el(i, j, this->at(i, j) + other.at(i, j));

  return result;
}

Matrix Matrix::operator-(const Matrix &other) const {
  if (this->rows != other.rows || this->columns != other.columns)
    throw runtime_error("cannot diff matrix of difeerent order");

  Matrix result = Matrix(this->rows, this->columns);
  for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < this->columns; j++)
      result.update_el(i, j, this->at(i, j) - other.at(i, j));

  return result;
}

Matrix Matrix::operator*(float scalar) const {

  Matrix result = Matrix(this->rows, this->columns);
  for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < this->columns; j++)
      result.update_el(i, j, (this->at(i, j) * scalar));

  return result;
}

Matrix Matrix::operator*(const Matrix &other) const {
  if (this->columns != other.rows)
    throw runtime_error("to multpl two matrix, A.columns needs be == B.lines");

  Matrix result = Matrix(this->rows, other.columns);

  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < other.columns; j++) {

      float sum = 0;
      for (int k = 0; k < this->columns; k++)
        sum += this->mtr[i][k] * other.mtr[k][j];
      result.update_el(i, j, sum);
    }
  }

  return result;
}

bool Matrix::operator==(const Matrix &other) const {
  if (this->rows != other.rows || this->columns != other.columns)
    return false;

  for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < this->columns; j++)
      if (this->mtr[i][j] != other.mtr[i][j])
        return false;

  return true;
}

stringstream Matrix::print_class() const {
  stringstream ss("");

  if (this->is_square())
    ss << "square" << endl;
  if (this->is_identity())
    ss << "identity" << endl;
  if (this->is_null())
    ss << "null" << endl;
  if (this->is_column())
    ss << "column" << endl;
  if (this->is_row())
    ss << "line" << endl;
  if (this->is_diagonal())
    ss << "diagonal" << endl;
  if (this->is_upper_tri())
    ss << "upper triangular" << endl;
  if (this->is_lower_tri())
    ss << "lower triangular" << endl;
  if (this->is_symmetric())
    ss << "symmetric" << endl;
  if (this->is_antisymmetric())
    ss << "antisymmetric" << endl;
  if (this->is_scalar())
    ss << "scalar" << endl;

  return ss;
}

stringstream Matrix::print() const {
  stringstream ss("");
  ss << "Matrix " << this->rows << "X" << this->columns << endl;
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->columns; j++)
      ss << "[" << this->mtr[i][j] << "]";
    ss << endl;
  }
  ss << "----" << endl;

  return ss;
}

// ---

void Matrix::init_mtr() {
  if (this->rows > 0 && this->columns > 0) {
    this->mtr = new float *[rows];
    for (int i = 0; i < this->rows; i++) {
      this->mtr[i] = new float[columns];
    }
  } else {
    throw runtime_error("null matrix dimentions");
  }
}

void Matrix::clear_mtr() {
  if (this->mtr != nullptr) {
    for (int i = 0; i < this->rows; i++)
      delete[](this->mtr[i]);
    delete[](this->mtr);
  }
}

double Matrix::det_order_2() const {
  if (this->rows != 2 || this->columns != 2)
    throw runtime_error("invalid matrix dimentions");

  return ((this->mtr[0][0] * this->mtr[1][1]) -
          (this->mtr[0][1] * this->mtr[1][0]));
}

double Matrix::det_order_3() const {
  long main_diagonal = 0;
  main_diagonal += this->mtr[0][0] * this->mtr[1][1] * this->mtr[2][2];
  main_diagonal += this->mtr[0][1] * this->mtr[1][2] * this->mtr[2][0];
  main_diagonal += this->mtr[0][2] * this->mtr[1][0] * this->mtr[2][1];

  long sec_diagonal = 0;
  sec_diagonal += mtr[2][0] * mtr[1][1] * mtr[0][2];
  sec_diagonal += mtr[2][1] * mtr[1][2] * mtr[0][0];
  sec_diagonal += mtr[2][2] * mtr[1][0] * mtr[0][1];

  return main_diagonal - sec_diagonal;
}

double Matrix::det_order_n() const {
  if (this->rows <= 3 || this->columns <= 3)
    throw runtime_error("expected dimentions > 3");
  if (this->rows != this->columns)
    throw runtime_error("matrix not square. cannot calc det");

  unsigned n = this->rows;

  if (_line_or_column_zero(this->mtr, n))
    return 0;

  double result = 0;
  for (int i = 0; i < n; i++) {
    result += (this->mtr[0][i] * this->cofactor(0, i));
  }

  return result;
}

bool _line_or_column_zero(float **mtr, int n) {

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
    // chekc lines
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

void _copy_mtr(float **src, float **dest, unsigned lines, unsigned columns) {
  for (int i = 0; i < lines; i++)
    for (int j = 0; j < columns; j++)
      dest[i][j] = src[i][j];
}

bool _vector_can_fill_mtr(const vector<float> vec, unsigned mtr_lines,
                          unsigned mtr_columns) {
  return (vec.size() == mtr_lines * mtr_columns);
}

void _check_mtr(float **mtr) {
  if (mtr == nullptr)
    throw runtime_error("null pointer exception");
}
