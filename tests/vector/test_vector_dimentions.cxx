#include <cmath>
#include <gtest/gtest.h>

#include "../utils.h"
#include "vector_lib.h"

using std::string;
const double kTolerance = 1e-7;

/*
 * due to templates limitations, we'll use a fixed number of dimentions to test
 * using macros
 */
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(-999.9, 999.9);

using namespace t_utils;

#define TEST_DIM(DIM)                                                          \
  TEST(VectorDimentions, SumVec##DIM) {                                        \
    Vector<DIM> u, v, w;                                                       \
    Vector<DIM> lhs, rhs;                                                      \
    u = genRandVector<DIM>(gen, dis);                                          \
    v = genRandVector<DIM>(gen, dis);                                          \
    w = genRandVector<DIM>(gen, dis);                                          \
                                                                               \
    lhs = u + (v + w);                                                         \
    rhs = (u + v) + w;                                                         \
    for (size_t i = 0; i < DIM; i++)                                           \
      EXPECT_NEAR(lhs.coord(i), rhs.coord(i), kTolerance);                     \
                                                                               \
    lhs = u + v;                                                               \
    rhs = v + u;                                                               \
    for (size_t i = 0; i < DIM; i++)                                           \
      EXPECT_NEAR(lhs.coord(i), rhs.coord(i), kTolerance);                     \
  }                                                                            \
                                                                               \
  TEST(VectorDimentions, MultplVec##DIM) {                                     \
    Vector<DIM> u, v;                                                          \
    double a, b;                                                               \
                                                                               \
    u = genRandVector<DIM>(gen, dis);                                          \
    v = genRandVector<DIM>(gen, dis);                                          \
                                                                               \
    Vector<DIM> lhs, rhs;                                                      \
                                                                               \
    a = dis(gen);                                                              \
    b = dis(gen);                                                              \
    lhs = a * (u + v);                                                         \
    rhs = a * u + a * v;                                                       \
    for (size_t i = 0; i < DIM; i++)                                           \
      EXPECT_NEAR(lhs.coord(i), rhs.coord(i), kTolerance);                     \
                                                                               \
    lhs = (a + b) * u;                                                         \
    rhs = a * u + b * u;                                                       \
    for (size_t i = 0; i < DIM; i++)                                           \
      EXPECT_NEAR(lhs.coord(i), rhs.coord(i), kTolerance);                     \
                                                                               \
    lhs = (a * b) * u;                                                         \
    rhs = a * (b * u);                                                         \
    for (size_t i = 0; i < DIM; i++)                                           \
      EXPECT_NEAR(lhs.coord(i), rhs.coord(i), kTolerance);                     \
                                                                               \
    lhs = 1 * u;                                                               \
    rhs = u;                                                                   \
    EXPECT_EQ(lhs, rhs);                                                       \
  }

TEST_DIM(1);
TEST_DIM(2);
TEST_DIM(3);
TEST_DIM(4);
TEST_DIM(5);
TEST_DIM(6);
TEST_DIM(8);
TEST_DIM(9);
TEST_DIM(10);
