
#include <gtest/gtest.h>

#include "matrix_lib.h"
#include "utils.h"


TEST(MatrixBasics, GetLineColumn) {
  Matrix<int> test_mtr = Matrix<int>(4,2);

  EXPECT_EQ(test_mtr.row_size(), 4);
  EXPECT_EQ(test_mtr.column_size(), 2);
}

TEST(MatrixBasics, Transpose) {
  Matrix<float> test_mtr = Matrix<float>(4,4);
  test_mtr.set_elements(std::vector<float>{
      1,2,3,4,
      8,7,6,5,
      2,2,2,2,
      4,4,4,4
      });
  Matrix<float> transposed_mtr = test_mtr.transpose();

  for(int i=0; i < 4; i++)
    for(int j=0; j < 4; j++)
      EXPECT_EQ(test_mtr.at(i, j), transposed_mtr.at(j, i));
}


TEST(MatrixBasics, Stroke) {
  Matrix<int> test_mtr = Matrix<int>(4,4);
  int stroke;

  test_mtr.set_elements(std::vector<int>{
      1,1,1,1,
      1,1,1,1,
      1,1,1,1,
      1,1,1,1
      });
  stroke = 4;

  EXPECT_EQ(stroke, test_mtr.stroke());


  test_mtr = Matrix<int>(6,6);
  test_mtr.set_elements(std::vector<int> {
      7,0,0,0,0,0,
      0,7,0,0,0,0,
      0,0,7,0,0,0,
      0,0,0,7,0,0,
      0,0,0,0,7,0,
      0,0,0,0,0,7,
      });
  stroke = 42;

  EXPECT_EQ(stroke, test_mtr.stroke());
}


TEST(MatrixBasics, Sum) {
  Matrix<int> test_mtr1 = Matrix<int>(4,4);
  test_mtr1.set_elements(std::vector<int>{
      2,2,2,2,
      2,2,2,2,
      2,2,2,2,
      2,2,2,2
      });
  Matrix<int> test_mtr2 = Matrix<int>(4,4);
  test_mtr2.set_elements(std::vector<int>{
      1,1,1,1,
      1,1,1,1,
      1,1,1,1,
      1,1,1,1
      });

  Matrix<int> sum_result = test_mtr1 + test_mtr2;

  Matrix<int> expected = Matrix<int>(4,4);
  expected.set_elements(std::vector<int>{
      3,3,3,3,
      3,3,3,3,
      3,3,3,3,
      3,3,3,3
      });

  EXPECT_EQ(expected, sum_result);

}


TEST(MatrixBasics, Diff) {
  Matrix<int> test_mtr1 = Matrix<int>(4,4);
  test_mtr1.set_elements(std::vector<int>{
      3,3,3,3,
      3,3,3,3,
      3,3,3,3,
      3,3,3,3
      });
  Matrix<int> test_mtr2 = Matrix<int>(4,4);
  test_mtr2.set_elements(std::vector<int>{
      1,1,1,1,
      1,1,1,1,
      1,1,1,1,
      1,1,1,1
      });

  Matrix<int> diff_result = test_mtr1 - test_mtr2;

  Matrix<int> expected = Matrix<int>(4,4);
  expected.set_elements(std::vector<int>{
      2,2,2,2,
      2,2,2,2,
      2,2,2,2,
      2,2,2,2
      });

  EXPECT_EQ(expected, diff_result);

}


TEST(MatrixBasics, MultiplScalar) {
  Matrix<int> test_mtr = Matrix<int>(6,6);
  test_mtr.set_elements(std::vector<int>{
      7,7,7,7,7,7,
      7,7,7,7,7,7,
      7,7,7,7,7,7,
      7,7,7,7,7,7,
      7,7,7,7,7,7,
      7,7,7,7,7,7
      });

  Matrix<int> multpl_result = test_mtr * 6;

  Matrix<int> expected = Matrix<int>(6,6);
  expected.set_elements(std::vector<int>{
      42,42,42,42,42,42,
      42,42,42,42,42,42,
      42,42,42,42,42,42,
      42,42,42,42,42,42,
      42,42,42,42,42,42,
      42,42,42,42,42,42,
      });

  EXPECT_EQ(expected, multpl_result);
}


TEST(MatrixBasics, MultiplAnotherMtr) {
  Matrix<int> test_mtr1 = Matrix<int>(4,4);
  Matrix<int> test_mtr2 = Matrix<int>(4,4);
  Matrix<int> expected = Matrix<int>(4,4);

  test_mtr1.set_elements(std::vector<int>{
      2,3,1,2,
      1,1,1,1,
      2,2,2,2,
      2,1,3,2
      });
  test_mtr2.set_elements(std::vector<int>{
      5,1,3,2,
      2,1,3,9,
      2,1,3,2,
      2,1,3,2
      });
  expected.set_elements({
      22, 8, 24, 37,
      11, 4, 12, 15,
      22, 8, 24, 30,
      22, 8, 24, 23
      });

  EXPECT_EQ(expected, test_mtr1 * test_mtr2);


  test_mtr1 = Matrix<int>(2,4);
  test_mtr2 = Matrix<int>(4,2);
  expected = Matrix<int>(2,2);

  test_mtr1.set_elements(std::vector<int>{
      1,2,3,4,
      3,3,3,3
      });
  test_mtr2.set_elements(std::vector<int>{
      1,2,
      3,4,
      7,7,
      7,7,
      });
  expected.set_elements(std::vector<int>{
      56, 59,
      54, 60
      });

  EXPECT_EQ(expected, test_mtr1 * test_mtr2);
}

TEST(MatrixBasics, Comparator) {
  Matrix<int> test_mtr1 = Matrix<int>(4,4);
  Matrix<int> test_mtr2 = Matrix<int>(4,4);
  Matrix<int> test_mtr3 = Matrix<int>(4,4);
  Matrix<int> test_mtr4 = Matrix<int>(2,2);

  test_mtr1.set_elements(std::vector<int>{
      1,2,3,4,
      4,3,2,1,
      1,2,3,4,
      4,3,2,1,
      });
  test_mtr2.set_elements(std::vector<int>{
      1,2,3,4,
      4,3,2,1,
      1,2,3,4,
      4,3,2,1,
      });
  EXPECT_TRUE(test_mtr1 == test_mtr2);

  test_mtr3.set_elements(std::vector<int>{
      1,2,3,4,
      1,2,3,4,
      1,2,3,4,
      1,2,3,4,
      });
  EXPECT_FALSE(test_mtr1 == test_mtr3);

  test_mtr4.set_elements(std::vector<int>{
      1,1,
      1,1
      });
  EXPECT_FALSE(test_mtr1 == test_mtr4);
}


