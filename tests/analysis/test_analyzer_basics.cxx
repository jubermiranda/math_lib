#include <gtest/gtest.h>
#include "analysis/analysis.h"

using namespace math_lib;

const double kTolerance = 1e-7;

class AnalysisTest : public ::testing::Test {
protected:
  void SetUp() override {
    analysis::AnalysisCreateInfo create_info{};
    analyzer = analysis::Analyzer::create(create_info);
    ASSERT_NE(analyzer, nullptr);
  }

  std::unique_ptr<analysis::Analyzer> analyzer;
};

TEST_F(AnalysisTest, MeanOfPositiveIntegers) {
  const std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
  ASSERT_NEAR(analyzer->mean(data), 3.0, kTolerance);
}

TEST_F(AnalysisTest, MeanWithNegativeNumbers) {
  const std::vector<double> data = {-1.0, -2.0, 0.0, 1.0, 2.0};
  ASSERT_NEAR(analyzer->mean(data), 0.0, kTolerance);
}

TEST_F(AnalysisTest, MeanOfSingleElement) {
  const std::vector<double> data = {42.0};
  ASSERT_NEAR(analyzer->mean(data), 42.0, kTolerance);
}

TEST_F(AnalysisTest, MeanOfEmptyVector) {
  const std::vector<double> data = {};
  ASSERT_DOUBLE_EQ(analyzer->mean(data), 0.0);
}

TEST_F(AnalysisTest, MeanOfDoubleNumbers) {
  const std::vector<double> data = { 1.34, 2.45, 3.56, 4.67 };
  ASSERT_NEAR(analyzer->mean(data), 3.005, kTolerance);
}

TEST_F(AnalysisTest, StdDevOfSimpleSet) {
  const std::vector<double> data = {2.0, 4.0, 4.0, 4.0, 5.0, 5.0, 7.0, 9.0};
  ASSERT_NEAR(analyzer->stddev(data), 2.0, kTolerance);
}
