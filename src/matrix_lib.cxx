#include "../include/matrix_lib.h"

using namespace std;

string mtr_class(int **);

Matrix::Matrix(unsigned lines, unsigned columns) : lines(lines), columns(columns) {
  this->init_mtr();
  this->classification = mtr_class(this->mtr);
}

Matrix::~Matrix() {
  if (this->mtr != nullptr) {
    for (int i = 0; i < lines; i++)
      free(mtr[i]);
    free(mtr);
  }
}

void Matrix::init_mtr(){
  if(this->lines > 0 && this->columns > 0){
    this->mtr = new int*[lines];
    for(int i=0; i < this->lines; i++){
      this->mtr[i] = new int[columns];
    }
  } else {
    throw runtime_error("null matrix dimentions");
  }
}
