#include <gtest/gtest.h>

#include "matrix_lib.h"
#include "utils.h"

using namespace std;

class MatrixLibFixture : public ::testing::Test {
protected:
  void SetUp() override {
    this->test_mtr = new Matrix(lines, columns);
    vector<int> mtr_elements = {
      1,0,0,0,
      0,1,0,0,
      0,0,1,0,
      0,0,0,1
    };
    this->test_mtr->set_elements(mtr_elements);
  }

  void TearDown() override {
    delete this->test_mtr;
  }

  unsigned lines = 4;
  unsigned columns = 4;
  Matrix *test_mtr;
};


TEST_F(MatrixLibFixture, CreatedMtrTest) {
  ASSERT_TRUE(test_mtr != nullptr);
  EXPECT_EQ(lines, test_mtr->get_lines());
  EXPECT_EQ(columns, test_mtr->get_columns());
}

TEST_F(MatrixLibFixture, PrintMtrElements) {
  string mtr_string = this->test_mtr->print().str();

  unsigned expected_0_ocrr = 12;
  unsigned expected_1_ocrr = 4;

  unsigned mtr_0_ocrr = t_utils::count_ocr(mtr_string, "0");
  unsigned mtr_1_ocrr = t_utils::count_ocr(mtr_string, "1");

  EXPECT_EQ(expected_0_ocrr, mtr_0_ocrr);
  EXPECT_EQ(expected_1_ocrr, mtr_1_ocrr);
}



