#include "matrix_lib.h"

using namespace std;

string mtr_classes(int **, unsigned, unsigned);
bool is_null(int **, unsigned, unsigned);
bool is_identity(int **, unsigned, unsigned);

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
    this->mtr = new int *[lines];
    for (int i = 0; i < this->lines; i++) {
      this->mtr[i] = new int[columns];
    }
  } else {
    throw runtime_error("null matrix dimentions");
  }
}

void Matrix::set_elements(const int *el) {
  throw runtime_error("not implemented yet");
}

void Matrix::set_elements(const vector<int> el) {
  if (el.size() != (this->lines * this->columns))
    throw runtime_error("invalid vector");
  if (this->mtr == nullptr)
    throw runtime_error("null pointer exception");

  for (int i = 0; i < this->lines; i++)
    for (int j = 0; j < this->columns; j++)
      this->mtr[i][j] = el.at((i * columns + j));
}

void Matrix::update_el(unsigned line, unsigned column, int new_el) {
  if (this->mtr == nullptr)
    throw runtime_error("null pointer exception");
  if (line >= this->lines || column >= this->columns)
    throw runtime_error("index out of range");

  this->mtr[line][column] = new_el;
}

int Matrix::at(unsigned line, unsigned column) const {
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
  string result = mtr_classes(this->mtr, this->lines, this->columns);
  stringstream ss(result);
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

int Matrix::stroke() const {
  if (this->lines != this->columns)
    throw runtime_error("mtr not square");

  int sum = 0;
  for (int i = 0; i < this->lines; i++)
    sum += this->mtr[i][i];

  return sum;
}

void Matrix::clear_mtr() {
  if (this->mtr != nullptr) {
    for (int i = 0; i < this->lines; i++)
      free(this->mtr[i]);
    free(this->mtr);
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

string mtr_classes(int **mtr_vector, unsigned lines, unsigned columns) {
  stringstream ss("");

  if (lines == columns)
    ss << "square" << endl;
  if (is_null(mtr_vector, lines, columns))
    ss << "null" << endl;
  if (is_identity(mtr_vector, lines, columns))
    ss << "identity" << endl;

  return ss.str();
}

bool is_identity(int **mtr, unsigned lines, unsigned columns) {
  for (int i = 0; i < lines; i++) {
    for (int j = 0; j < columns; j++) {
      int aux = (i == j) ? 1 : 0;
      if (mtr[i][j] != aux)
        return false;
    }
  }

  return true;
}

bool is_null(int **mtr, unsigned lines, unsigned columns) {
  for (int i = 0; i < lines; i++)
    for (int j = 0; j < columns; j++)
      if (mtr[i][j] != 0)
        return false;

  return true;
}
