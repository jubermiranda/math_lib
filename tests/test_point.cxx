#include <gtest/gtest.h>

#include "point.h"

using std::string;

TEST(PointBasics, ContructorAndAttr) {
  Point p;

  //constructors
  p = Point();
  ASSERT_EQ(p.x, 0.0);
  ASSERT_EQ(p.y, 0.0);
  ASSERT_EQ(p.z, 0.0);

  p = Point(1, 2, 3);
  ASSERT_EQ(p.x, 1.0);
  ASSERT_EQ(p.y, 2.0);
  ASSERT_EQ(p.z, 3.0);

  Point copy_point(p);
  ASSERT_EQ(copy_point.x, 1.0);
  ASSERT_EQ(copy_point.y, 2.0);
  ASSERT_EQ(copy_point.z, 3.0);


  // attr operator
  Point another_p(-4, -3, -2);
  p = another_p;
  ASSERT_EQ(p.x, -4.0);
  ASSERT_EQ(p.y, -3.0);
  ASSERT_EQ(p.z, -2.0);
}

TEST(PointBasics, Operators) {
  Point p1, p2;
  Point expected;

  //sum
  p1 = Point(1, 2, 3);
  p2 = Point(1, 2, 3);
  EXPECT_EQ(p1 + p2, Point(2, 4, 6));

  p1 = Point(0, 0, 0);
  p2 = Point(0, 0, 0);
  EXPECT_EQ(p1 + p2, Point());

  p1 = Point(-4, -3, -2);
  p2 = Point(0, 1, 2);
  EXPECT_EQ(p1 + p2, Point(-4, -2, 0));

  //diff
  p1 = Point(2, 5, 10);
  p2 = Point(2, 3, 4);
  EXPECT_EQ(p1 - p2, Point(0, 2, 6));
  
  p1 = Point(-5, -4, -3);
  p2 = Point(-3, 3, 0);
  EXPECT_EQ(p1 - p2, Point(-2, -7, -3));

  //scalar
  p1 = Point(1, 2, 3);
  EXPECT_EQ(p1 * 2, Point(2, 4, 6));
  EXPECT_EQ(p1 * 4, Point(4, 8, 12));
  EXPECT_EQ(p1 * -1, Point(-1, -2, -3));
  EXPECT_EQ(p1 * 0.5, Point(0.5, 1, 1.5));
}
