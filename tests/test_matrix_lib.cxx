#include <gtest/gtest.h>

#include "matrix_lib.h"
#include "utils.h"

using namespace std;

class MatrixLibFixture : public ::testing::Test {
protected:
  void SetUp() override {
  }

  void TearDown() override {
  }

};


TEST_F(MatrixLibFixture, CreateGetLineColumns) {
  Matrix test_mtr = Matrix(4,2);

  EXPECT_EQ(test_mtr.get_lines(), 4);
  EXPECT_EQ(test_mtr.get_columns(), 2);
}

TEST_F(MatrixLibFixture, PrintMtrElements) {
  Matrix test_mtr = Matrix(4,4);
  vector<int> elements = {
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


TEST_F(MatrixLibFixture, MtrClassIdentity) {
  string result_class;
  vector<int> mtr_elements;

  Matrix test_mtr = Matrix(4,4);
  mtr_elements = {
      1,0,0,0,
      0,1,0,0,
      0,0,1,0,
      0,0,0,1
  };
  test_mtr.set_elements(mtr_elements);
  result_class = test_mtr.print_class().str();

  EXPECT_TRUE(t_utils::is_sub_str(result_class, "identity"));
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "square"));

  mtr_elements.clear();


  test_mtr = Matrix(2,2);
  mtr_elements = {
    1,0,
    0,1
  };
  test_mtr.set_elements(mtr_elements);
  result_class = test_mtr.print_class().str();

  EXPECT_TRUE(t_utils::is_sub_str(result_class, "identity"));
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "square"));
}


TEST_F(MatrixLibFixture, MtrClassNull) {
  Matrix test_mtr = Matrix(4,2);
  vector<int> elements = {
    0,0,
    0,0,
    0,0,
    0,0
  };
  test_mtr.set_elements(elements);
  string result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "null"));

  test_mtr = Matrix(2,4);
  elements.clear();
  elements = {
    0,0,0,0,
    0,0,0,0
  };
  test_mtr.set_elements(elements);
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "null"));
}


TEST_F(MatrixLibFixture, MtrClassSquare) {
  Matrix test_mtr = Matrix(4,4);
  test_mtr.set_elements(vector<int>{
      2,2,2,2,
      2,2,2,2,
      2,2,2,2,
      2,2,2,2
  });
  string result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "square"));


  test_mtr = Matrix(2,2);
  test_mtr.set_elements(vector<int>{
      4,4,
      4,4
  });
  result_class = test_mtr.print_class().str();
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "square"));



  test_mtr = Matrix(4,2);
  test_mtr.set_elements(vector<int>{
      4,2,
      4,2,
      4,2,
      4,2
  });
  result_class = test_mtr.print_class().str();
  EXPECT_FALSE(t_utils::is_sub_str(result_class, "square"));
}


TEST_F(MatrixLibFixture, MtrTranspose) {
  Matrix test_mtr = Matrix(4,4);
  test_mtr.set_elements(vector<int>{
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



TEST_F(MatrixLibFixture, MtrStroke) {
  Matrix test_mtr = Matrix(4,4);
  test_mtr.set_elements(vector<int>{
      1,1,1,1,
      1,1,1,1,
      1,1,1,1,
      1,1,1,1
      });
  EXPECT_EQ(4, test_mtr.stroke());

  test_mtr = Matrix(6,6);
  test_mtr.set_elements(vector<int> {
      7,0,0,0,0,0,
      0,7,0,0,0,0,
      0,0,7,0,0,0,
      0,0,0,7,0,0,
      0,0,0,0,7,0,
      0,0,0,0,0,7,
      });
  EXPECT_EQ(42, test_mtr.stroke());
}


TEST_F(MatrixLibFixture, MtrAritimeticOpr) {
  Matrix test_mtr1 = Matrix(4,4);
  test_mtr1.set_elements(vector<int>{
      2,2,2,2,
      2,2,2,2,
      2,2,2,2,
      2,2,2,2
      });
  Matrix test_mtr2 = Matrix(4,4);
  test_mtr2.set_elements(vector<int>{
      1,1,1,1,
      1,1,1,1,
      1,1,1,1,
      1,1,1,1
      });

  //sum
  Matrix sum_result = test_mtr1 + test_mtr2;
  for(int i=0; i < 4; i++)
    for(int j=0; j < 4; j++)
      EXPECT_EQ(3, sum_result.at(i, j));

  //diff
  Matrix diff_result = test_mtr1 - test_mtr2;
  for(int i=0; i < 4; i++)
    for(int j=0; j < 4; j++)
      EXPECT_EQ(1, diff_result.at(i, j));

  Matrix multpl_result = test_mtr1 * 4;
  for(int i=0; i < 4; i++)
    for(int j=0; j < 4; j++)
      EXPECT_EQ(8, diff_result.at(i, j));
}
