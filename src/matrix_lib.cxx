#include "matrix_lib.h"

using namespace std;

string mtr_class(int **);

Matrix::Matrix(unsigned lines, unsigned columns)
    : lines(lines), columns(columns) {
  this->init_mtr();
  this->classification = mtr_class(this->mtr);
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
      this->mtr[i][j] = el.at((i * j + j));
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

void Matrix::clear_mtr() {
  if (this->mtr != nullptr) {
    for (int i = 0; i < this->lines; i++)
      free(this->mtr[i]);
    free(this->mtr);
  }
}

string mtr_class(int **mtr_vector) {
  return "TODO";
}
