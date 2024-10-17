#include <gtest/gtest.h>
#include <vector>

#include "vector_lib.h"
#include "utils.h"

using std::string;

TEST(VectorBasics, DistanceMod) {
  Vector a(3, 4, 5);

  EXPECT_EQ(a.mod(), 0);//TODO
}
