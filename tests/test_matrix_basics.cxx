
#include <gtest/gtest.h>

#include "matrix_lib.h"
#include "utils.h"

using std::vector;
using std::string;


TEST(MatrixBasics, GetLineColumn) {
  Matrix test_mtr = Matrix(4,2);

  EXPECT_EQ(test_mtr.get_lines(), 4);
  EXPECT_EQ(test_mtr.get_columns(), 2);
}

TEST(MatrixBasics, PrintElements) {
  Matrix test_mtr = Matrix(4,4);
  vector<float> elements = {
      1,0,0,0,
      0,1,0,0,
      0,0,1,0,
      0,0,0,1
  };
  test_mtr.set_elements(elements);

  string mtr_string = test_mtr.print().str();

  unsigned expected_0_ocrr = 12;
  unsigned expected_1_ocrr = 4;

  unsigned mtr_0_ocrr = t_utils::count_ocr(mtr_string, "0");
  unsigned mtr_1_ocrr = t_utils::count_ocr(mtr_string, "1");

  EXPECT_EQ(expected_0_ocrr, mtr_0_ocrr);
  EXPECT_EQ(expected_1_ocrr, mtr_1_ocrr);
}

TEST(MatrixBasics, Transpose) {
  Matrix test_mtr = Matrix(4,4);
  test_mtr.set_elements(vector<float>{
      1,2,3,4,
      8,7,6,5,
      2,2,2,2,
      4,4,4,4
      });
  Matrix transposed_mtr = test_mtr.transpose();

  for(int i=0; i < 4; i++)
    for(int j=0; j < 4; j++)
      EXPECT_EQ(test_mtr.at(i, j), transposed_mtr.at(j, i));

}



TEST(MatrixBasics, Stroke) {
  Matrix test_mtr = Matrix(4,4);
  double stroke;

  test_mtr.set_elements(vector<float>{
      1,1,1,1,
      1,1,1,1,
      1,1,1,1,
      1,1,1,1
      });
  stroke = 4;

  EXPECT_EQ(stroke, test_mtr.stroke());


  test_mtr = Matrix(6,6);
  test_mtr.set_elements(vector<float> {
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
  Matrix test_mtr1 = Matrix(4,4);
  test_mtr1.set_elements(vector<float>{
      2,2,2,2,
      2,2,2,2,
      2,2,2,2,
      2,2,2,2
      });
  Matrix test_mtr2 = Matrix(4,4);
  test_mtr2.set_elements(vector<float>{
      1,1,1,1,
      1,1,1,1,
      1,1,1,1,
      1,1,1,1
      });

  Matrix sum_result = test_mtr1 + test_mtr2;

  Matrix expected = Matrix(4,4);
  expected.set_elements(vector<float>{
      3,3,3,3,
      3,3,3,3,
      3,3,3,3,
      3,3,3,3
      });

  EXPECT_EQ(expected, sum_result);

}


TEST(MatrixBasics, Diff) {
  Matrix test_mtr1 = Matrix(4,4);
  test_mtr1.set_elements(vector<float>{
      3,3,3,3,
      3,3,3,3,
      3,3,3,3,
      3,3,3,3
      });
  Matrix test_mtr2 = Matrix(4,4);
  test_mtr2.set_elements(vector<float>{
      1,1,1,1,
      1,1,1,1,
      1,1,1,1,
      1,1,1,1
      });

  Matrix diff_result = test_mtr1 - test_mtr2;

  Matrix expected = Matrix(4,4);
  expected.set_elements(vector<float>{
      2,2,2,2,
      2,2,2,2,
      2,2,2,2,
      2,2,2,2
      });

  EXPECT_EQ(expected, diff_result);

}


TEST(MatrixBasics, MultiplScalar) {
  Matrix test_mtr = Matrix(6,6);
  test_mtr.set_elements(vector<float>{
      7,7,7,7,7,7,
      7,7,7,7,7,7,
      7,7,7,7,7,7,
      7,7,7,7,7,7,
      7,7,7,7,7,7,
      7,7,7,7,7,7
      });

  Matrix multpl_result = test_mtr * 6;

  Matrix expected = Matrix(6,6);
  expected.set_elements(vector<float>{
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
  Matrix test_mtr1 = Matrix(4,4);
  Matrix test_mtr2 = Matrix(4,4);
  Matrix expected = Matrix(4,4);

  test_mtr1.set_elements(vector<float>{
      2,3,1,2,
      1,1,1,1,
      2,2,2,2,
      2,1,3,2
      });
  test_mtr2.set_elements(vector<float>{
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


  test_mtr1 = Matrix(2,4);
  test_mtr2 = Matrix(4,2);
  expected = Matrix(2,2);

  test_mtr1.set_elements(vector<float>{
      1,2,3,4,
      3,3,3,3
      });
  test_mtr2.set_elements(vector<float>{
      1,2,
      3,4,
      7,7,
      7,7,
      });
  expected.set_elements(vector<float>{
      56, 59,
      54, 60
      });

  EXPECT_EQ(expected, test_mtr1 * test_mtr2);
}

TEST(MatrixBasics, Comparator) {
  Matrix test_mtr1 = Matrix(4,4);
  Matrix test_mtr2 = Matrix(4,4);
  Matrix test_mtr3 = Matrix(4,4);
  Matrix test_mtr4 = Matrix(2,2);

  test_mtr1.set_elements(vector<float>{
      1,2,3,4,
      4,3,2,1,
      1,2,3,4,
      4,3,2,1,
      });
  test_mtr2.set_elements(vector<float>{
      1,2,3,4,
      4,3,2,1,
      1,2,3,4,
      4,3,2,1,
      });
  EXPECT_TRUE(test_mtr1 == test_mtr2);

  test_mtr3.set_elements(vector<float>{
      1,2,3,4,
      1,2,3,4,
      1,2,3,4,
      1,2,3,4,
      });
  EXPECT_FALSE(test_mtr1 == test_mtr3);

  test_mtr4.set_elements(vector<float>{
      1,1,
      1,1
      });
  EXPECT_FALSE(test_mtr1 == test_mtr4);
}


