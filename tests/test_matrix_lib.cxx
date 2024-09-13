#include <gtest/gtest.h>

using namespace std;

class MatrixLibFixture : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(MatrixLibFixture, InitialTestShouldFailsBeforeImpl) {
  ASSERT_EQ(4, 2);
}

