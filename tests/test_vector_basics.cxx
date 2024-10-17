#include <gtest/gtest.h>
#include <vector>

#include "utils.h"
#include "vector_lib.h"

using std::string;

TEST(VectorBasics, DistanceMod) {
  Vector vec;

  vec = Vector(0, 0, 0);
  EXPECT_EQ(vec.mod(), 0);

  vec = Vector(2.4, 0, 0);
  EXPECT_EQ(vec.mod(), 2.4f);
  vec = Vector(4.2, 0, 0);
  EXPECT_EQ(vec.mod(), 4.2f);

  vec = Vector(0, 2, 0);
  EXPECT_EQ(vec.mod(), 2.0f);
  vec = Vector(0, 4, 0);
  EXPECT_EQ(vec.mod(), 4.0f);

  vec = Vector(0, 0, 2.2);
  EXPECT_EQ(vec.mod(), 2.2f);
  vec = Vector(0, 0, 4.4);
  EXPECT_EQ(vec.mod(), 4.4f);

  vec = Vector(1, 2, 2);
  EXPECT_EQ(vec.mod(), 3.0f);

  vec = Vector(-3, -4, 0);
  EXPECT_EQ(vec.mod(), 5.0f);
}
