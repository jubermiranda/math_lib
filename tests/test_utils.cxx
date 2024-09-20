#include <gtest/gtest.h>

#include "utils.h"

using namespace std;

TEST(UtilsTest, IsSubStrWorks) {
  string str = "hello world";
  string sub1 = "hello";
  string sub2 = "world";
  string sub3 = "test";

  EXPECT_TRUE(t_utils::is_sub_str(str, sub1));
  EXPECT_TRUE(t_utils::is_sub_str(str, sub2));
  EXPECT_FALSE(t_utils::is_sub_str(str, sub3));
}

TEST(UtilsTest, CountOcrWorks) {
  string str = "hello world! hello test";

  EXPECT_EQ(2, t_utils::count_ocr(str, "hello"));
  EXPECT_EQ(1, t_utils::count_ocr(str, "world"));
  EXPECT_EQ(0, t_utils::count_ocr(str, "zero"));
}
