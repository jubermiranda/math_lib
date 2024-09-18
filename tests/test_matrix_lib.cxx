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


  Matrix test_mtr2 = Matrix(2,2);
  mtr_elements = {
    1,0,
    0,1
  };
  test_mtr2.set_elements(mtr_elements);
  result_class = test_mtr2.print_class().str();

  EXPECT_TRUE(t_utils::is_sub_str(result_class, "identity"));
  EXPECT_TRUE(t_utils::is_sub_str(result_class, "square"));
}


TEST_F(MatrixLibFixture, MtrClassNull) {
  ASSERT_EQ(4,2);
}
