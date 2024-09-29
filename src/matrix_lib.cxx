#include "matrix_lib.h"

using namespace std;

double det_order_2(float **);
double det_order_3(float **);
double det_order_n(float **, unsigned);

Matrix::Matrix(unsigned lines, unsigned columns)
    : lines(lines), columns(columns) {
  this->init_mtr();
}

Matrix::Matrix(const Matrix &other)
    : lines(other.lines), columns(other.columns) {
  this->init_mtr();
}

Matrix::~Matrix() { this->clear_mtr(); }

void Matrix::init_mtr() {
  if (this->lines > 0 && this->columns > 0) {
    this->mtr = new float *[lines];
    for (int i = 0; i < this->lines; i++) {
      this->mtr[i] = new float[columns];
    }
  } else {
    throw runtime_error("null matrix dimentions");
  }
}

void Matrix::set_elements(const float *el) {
  throw runtime_error("not implemented yet");
}

void Matrix::set_elements(const vector<float> el) {
  if (el.size() != (this->lines * this->columns))
    throw runtime_error("invalid vector");
  if (this->mtr == nullptr)
    throw runtime_error("null pointer exception");

  for (int i = 0; i < this->lines; i++)
    for (int j = 0; j < this->columns; j++)
      this->mtr[i][j] = el.at((i * columns + j));
}

void Matrix::update_el(unsigned line, unsigned column, float new_el) {
  if (this->mtr == nullptr)
    throw runtime_error("null pointer exception");
  if (line >= this->lines || column >= this->columns)
    throw runtime_error("index out of range");

  this->mtr[line][column] = new_el;
}

float Matrix::at(unsigned line, unsigned column) const {
  if (line >= this->lines || column >= this->columns)
    throw runtime_error("index out of range");

  return this->mtr[line][column];
}

unsigned Matrix::get_lines() const { return this->lines; }

unsigned Matrix::get_columns() const { return this->columns; }

stringstream Matrix::print() const {
  stringstream ss("");
  ss << "Matrix " << this->lines << "X" << this->columns << endl;
  for (int i = 0; i < this->lines; i++) {
    for (int j = 0; j < this->columns; j++)
      ss << "[" << this->mtr[i][j] << "]";
    ss << endl;
  }
  ss << "----" << endl;

  return ss;
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
  if (this->is_line())
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

Matrix Matrix::transpose() const {
  Matrix result = Matrix(this->lines, this->columns);
  for (int i = 0; i < this->lines; i++) {
    for (int j = 0; j < this->columns; j++) {
      result.update_el(i, j, this->at(j, i));
    }
  }

  return result;
}

bool Matrix::is_identity() const {
  if (!this->is_square())
    return false;

  for (int i = 0; i < lines; i++) {
    for (int j = 0; j < columns; j++) {
      float aux = (i == j) ? 1 : 0;
      if (mtr[i][j] != aux)
        return false;
    }
  }

  return true;
}

bool Matrix::is_square() const { return (this->lines == this->columns); }

bool Matrix::is_null() const {
  for (int i = 0; i < this->lines; i++)
    for (int j = 0; j < this->columns; j++)
      if (this->mtr[i][j] != 0)
        return false;

  return true;
}

bool Matrix::is_column() const { return (this->columns == 1); }

bool Matrix::is_line() const { return (this->lines == 1); }

bool Matrix::is_diagonal() const {
  if (!this->is_square())
    return false;

  for (int i = 0; i < lines; i++)
    for (int j = 0; j < columns; j++)
      if (i != j && this->mtr[i][j] != 0)
        return false;

  return true;
}

bool Matrix::is_upper_tri() const {
  if (!this->is_square())
    return false;

  for (int i = 0; i < this->lines; i++)
    for (int j = 0; j < i; j++)
      if (this->mtr[i][j] != 0)
        return false;

  return true;
}

bool Matrix::is_lower_tri() const {
  if (!this->is_square())
    return false;

  for (int i = 0; i < this->lines; i++)
    for (int j = i + 1; j < this->columns; j++)
      if (this->mtr[i][j] != 0)
        return false;

  return true;
}

bool Matrix::is_symmetric() const {
  if (!this->is_square())
    return false;

  for (int i = 0; i < this->lines; i++)
    for (int j = i; j < this->columns; j++)
      if (this->mtr[i][j] != this->mtr[j][i])
        return false;

  return true;
}

bool Matrix::is_antisymmetric() const {
  if (!this->is_square())
    return false;

  for (int i = 0; i < this->lines; i++)
    if (this->mtr[i][i] != 0)
      return false;
  return true;
}

bool Matrix::is_scalar() const {
  if (!this->is_diagonal())
    return false;

  float diagonal_el = this->mtr[0][0];
  for (int i = 1; i < this->lines; i++)
    if (this->mtr[i][i] != diagonal_el)
      return false;

  return true;
}

float Matrix::stroke() const {
  if (this->lines != this->columns)
    throw runtime_error("mtr not square");

  float sum = 0;
  for (int i = 0; i < this->lines; i++)
    sum += this->mtr[i][i];

  return sum;
}

double Matrix::det() const {
  if (!this->is_square())
    throw runtime_error("cannot calc det. matrix not square");

  switch (this->lines) {
  case 1:
    return this->at(0, 0);
    break;

  case 2:
    return det_order_2(this->mtr);
    break;

  case 3:
    return det_order_3(this->mtr);
    break;

  default:
    return det_order_n(this->mtr, this->lines);
  }

  return 0;
}

void Matrix::clear_mtr() {
  if (this->mtr != nullptr) {
    for (int i = 0; i < this->lines; i++)
      delete[](this->mtr[i]);
    delete[](this->mtr);
  }
}

Matrix &Matrix::operator=(const Matrix &other) {
  if (this != &other) {
    this->clear_mtr();

    this->lines = other.lines;
    this->columns = other.columns;
    this->init_mtr();
  }
  return *this;
}

Matrix Matrix::operator+(const Matrix &other) const {
  if (this->lines != other.lines || this->columns != other.columns)
    throw runtime_error("cannot sum matrix of difeerent order");

  Matrix result = Matrix(this->lines, this->columns);
  for (int i = 0; i < this->lines; i++)
    for (int j = 0; j < this->columns; j++)
      result.update_el(i, j, this->at(i, j) + other.at(i, j));

  return result;
}

Matrix Matrix::operator-(const Matrix &other) const {
  if (this->lines != other.lines || this->columns != other.columns)
    throw runtime_error("cannot diff matrix of difeerent order");

  Matrix result = Matrix(this->lines, this->columns);
  for (int i = 0; i < this->lines; i++)
    for (int j = 0; j < this->columns; j++)
      result.update_el(i, j, this->at(i, j) - other.at(i, j));

  return result;
}

Matrix Matrix::operator*(float scalar) const {

  Matrix result = Matrix(this->lines, this->columns);
  for (int i = 0; i < this->lines; i++)
    for (int j = 0; j < this->columns; j++)
      result.update_el(i, j, (this->at(i, j) * scalar));

  return result;
}

Matrix Matrix::operator*(const Matrix &other) const {
  if (this->columns != other.lines)
    throw runtime_error("to multpl two matrix, A.columns needs be == B.lines");

  Matrix result = Matrix(this->lines, other.columns);

  for (int i = 0; i < this->lines; i++) {
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
  if (this->lines != other.lines || this->columns != other.columns)
    return false;

  for (int i = 0; i < this->lines; i++)
    for (int j = 0; j < this->columns; j++)
      if (this->mtr[i][j] != other.mtr[i][j])
        return false;

  return true;
}


// -----------------------------------------------------
//
// --- AUXILIAR FUNCTIONS

bool line_or_column_zero(float **mtr, int n);

double det_order_2(float **mtr) {
  return ((mtr[0][0] * mtr[1][1]) - (mtr[0][1] * mtr[1][0]));
}

double det_order_3(float **mtr) {
  long main_diagonal = 0;
  main_diagonal += mtr[0][0] * mtr[1][1] * mtr[2][2];
  main_diagonal += mtr[0][1] * mtr[1][2] * mtr[2][0];
  main_diagonal += mtr[0][2] * mtr[1][0] * mtr[2][1];

  long sec_diagonal = 0;
  sec_diagonal += mtr[2][0] * mtr[1][1] * mtr[0][2];
  sec_diagonal += mtr[2][1] * mtr[1][2] * mtr[0][0];
  sec_diagonal += mtr[2][2] * mtr[1][0] * mtr[0][1];

  return main_diagonal - sec_diagonal;
}

double det_order_n(float **mtr, unsigned n) {
  if(line_or_column_zero(mtr, n))
    return 0;
  
  throw runtime_error("not implemented yet");
  return 0;
}


bool line_or_column_zero(float **mtr, int n){

  for (int i = 0; i < n; i++) {
    // chekc columns
    if (mtr[0][i] == 0) {
      bool all_zero = true;
      for(int j=1; j < n; j++){
        if(mtr[j][i] != 0){
          all_zero = false;
          break;
        }
      }
      if(all_zero)
        return true;
    }
    // chekc lines
    if(mtr[i][0] == 0){
      bool all_zero = true;
      for(int j=1; j < n; j++){
        if(mtr[i][j] != 0){
          all_zero = false;
          break;
        }
      }
      if(all_zero)
        return true;
    }
  }
  
  return false;
}
