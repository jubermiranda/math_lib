#include <gtest/gtest.h>
#include <vector>

#include "matrix_lib.h"
#include "utils.h"

using std::vector;

TEST(MatrixDeterminant, MtrDetOrder1) {
  Matrix test_mtr = Matrix(1,1);
  double expected_det;

  test_mtr.set_elements(vector<float>{
      40
      });
  expected_det = 40;

  EXPECT_EQ(expected_det, test_mtr.det());
}

TEST(MatrixDeterminant, MtrDetOrder2) {
  Matrix test_mtr = Matrix(2,2);
  double expected_det;

  test_mtr.set_elements(vector<float>{
      22, 11,
      2,  5
      });
  expected_det = 88;

  EXPECT_EQ(expected_det, test_mtr.det());
}

TEST(MatrixDeterminant, MtrDetOrder3) {
  Matrix test_mtr(3,3);
  double expected_det;

  test_mtr.set_elements(vector<float>{
      1,2,3,
      4,5,6,
      7,8,9
      });
  expected_det = 0;
  EXPECT_EQ(expected_det, test_mtr.det());

  test_mtr.set_elements(vector<float>{
      6, 1,  1,
      4, -2, 5,
      2, 8,  7
      });
  expected_det = -306;
  EXPECT_EQ(expected_det, test_mtr.det());

  test_mtr.set_elements(vector<float>{
      10, -7, 3,
      -3, 6, 2,
      5, 8, 9
      });
  expected_det = -41;
  EXPECT_EQ(expected_det, test_mtr.det());


  test_mtr.set_elements(vector<float>{
      1, 0, 0,
      0, 1, 0,
      0, 0, 1
      });
  expected_det = 1;
  EXPECT_EQ(expected_det, test_mtr.det());
}

TEST(MatrixDeterminant, MtrDetOrder4){
  Matrix test_mtr(4,4);
  double expected;

  test_mtr.set_elements(vector<float>{
      1, 2, 3, 4,
      5, 6, 7, 8,
      9, 10, 11, 12,
      13, 14, 15, 16
  });
  expected = 0;

  EXPECT_EQ(expected, test_mtr.det());

  test_mtr.set_elements(vector<float>{
      1, 3, 1, 3,
      4, 1, -1, 0,
      0, 2, 2, 1,
      2, 1, -5, 1
  });
  expected = 56;

  EXPECT_EQ(expected, test_mtr.det());


  test_mtr.set_elements(vector<float>{
      4, 5, -3, 0,
      2, -1, 3, 1,
      1, -3, 2, 1,
      0, 2, -2, 5
  });
  expected = 210;

  EXPECT_EQ(expected, test_mtr.det());
}

TEST(MatrixDeterminant, MtrDetOrder5){
  Matrix test_mtr(5,5);
  double expected;

  test_mtr.set_elements(vector<float>{
      1, 2, 3, -3, 1,
      0, 4, 0, 0, 0,
      0, 1, 0, 1, 1,
      0, -6, 6, 1, 3,
      0, 2, 0, -1, 1
  });
  expected = -48;
  EXPECT_EQ(expected, test_mtr.det());

  test_mtr.set_elements(vector<float>{
      1, 3, 1, 3, 5,
      4, 1, -1, 0, 2,
      0, 2, 2, 1, 0,
      2, 1, -5, 1, 4,
      1, -2, 3, 1, 1
  });
  expected = -212;
  EXPECT_EQ(expected, test_mtr.det());
  
}

TEST(MatrixDeterminant, MtrDetOrder10){
  Matrix test_mtr(10, 10);
  double expected;

  test_mtr.set_elements(vector<float>{
      1,  3,  4,  2,  5,  7,  11, -9, 7,  1,
      0,  -5, 1,  1,  9, -4,  1,  3,  1,  1,
      -2, 3,  4,  2,  5,  7,  -4, 4,  7,  -1,
      4,  3,  1,  2,  5,  7,  1,  9,  7,  -1,
      1,  5,  4,  1,  5,  1,  9,  0,  7,  -1,
      2,  3,  0,  2,  5,  7,  1,  9,  7,  -1,
      -8, 3,  4,  2,  1,  7,  1,  -1, 7,  -1,
      6,  4,  -8, 2,  5,  2,  1,  7,  7,  -1,
      4,  4,  4,  2,  5,  7,  1,  1,  7,  -1,
      1, -6,  4,  2,  5,  7,  1,  2,  7,  -1,
  });
  //Need calc expected correct value
  expected = 7524720;
  EXPECT_EQ(expected, test_mtr.det());
}


TEST(MatrixDeterminant, LineOrColumnZeroDetIsZero) {
  Matrix test_mtr(4,4);
  double expected_det;

  test_mtr.set_elements(vector<float>{
      0, 0, 0, 0,
      5, 6, 7, 8,
      9, 10, 11, 12,
      13, 14, 15, 16
      });
  expected_det = 0;
  EXPECT_EQ(expected_det, test_mtr.det());

  test_mtr.set_elements(vector<float>{
      0, 2, 3, 4,
      0, 6, 7, 8,
      0, 10, 11, 12,
      0, 14, 15, 16
      });
  expected_det = 0;
  EXPECT_EQ(expected_det, test_mtr.det());

  test_mtr.set_elements(vector<float>{
      1, 1, 0, 1,
      1, 1, 0, 1,
      1, 1, 0, 1,
      1, 1, 0, 1,
      });
  expected_det = 0;
  EXPECT_EQ(expected_det, test_mtr.det());
}

//TODO p3, p4


TEST(MatrixDeterminant, MinorComplementaryOrder3){
  Matrix test_mtr(3,3);
  double expected;
  unsigned line, column;

  test_mtr.set_elements(vector<float>{
      2, 1, 3,
      -1, -2, 4,
      1, 0, -3,
  });

  line = 1;
  column = 2;
  expected = -1;
  EXPECT_EQ(expected, test_mtr.minor_comp(line, column));

  line = 0;
  column = 0;
  expected = 6;
  EXPECT_EQ(expected, test_mtr.minor_comp(line, column));
}

TEST(MatrixDeterminant, Cofactor){
  Matrix test_mtr(3,3);
  double expected;
  unsigned line, column;
  test_mtr.set_elements(vector<float>{
      2, 1, 3,
      -1, -2, 4,
      1, 0, -3,
  });

  line = 0;
  column = 0;
  expected = 6;

  EXPECT_EQ(expected, test_mtr.cofactor(line, column));

  line = 1;
  column = 2;
  expected = 1;

EXPECT_EQ(expected, test_mtr.cofactor(line, column));
}

