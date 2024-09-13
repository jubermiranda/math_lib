#include <gtest/gtest.h>

#include "../include/matrix_lib.h"

using namespace std;

class MatrixLibFixture : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}

  Matrix *test_mtr;
};

TEST_F(MatrixLibFixture, CreateMtr) {
  unsigned lines = 4;
  unsigned columns = 4;
  test_mtr = new Matrix(lines, columns);
  ASSERT_TRUE(test_mtr != nullptr);
  ASSERT_EQ(lines, test_mtr->get_lines());
  ASSERT_EQ(columns, test_mtr->get_columns());
}

TEST_F(MatrixLibFixture, InitMtrElements) {
  string lhs = "not implemented";
  string rhs = test_mtr->print_el().str();

  EXPECT_STREQ(lhs.c_str(), rhs.c_str());
}
