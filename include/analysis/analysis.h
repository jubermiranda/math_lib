#pragma once

#include <cstddef>
#include <memory>
#include <random>
#include <vector>

#include "core/execution_policy.h"

namespace math_lib {

namespace rand {

  class RandomProvider {
    private:
      std::mt19937 m_gen;
    public:
      explicit RandomProvider(unsigned int seed) : m_gen(seed) {}

      std::mt19937& gen() { return m_gen; }
  };

} // namespace Rand
  //

namespace dist {

  double exp(rand::RandomProvider& rand, double mean);
  double norm(rand::RandomProvider& rand, double mean, double stddev);
  double triangular(rand::RandomProvider& rand, double min, double mode, double max);
  double uniform(rand::RandomProvider& rand, double min, double max);
  int uniform_int(rand::RandomProvider& rand, int min, int max);
  size_t weighted_discrete(rand::RandomProvider& rand, const std::vector<double>& weights);
  double lognorm(rand::RandomProvider& rand, double mean, double stddev);

} // namespace Dist
  //

namespace analysis{

  enum class PercentileMethod {
    LINEAR_INTERPOLATION,
    NEAREST_RANK
  };

  struct AnalysisCreateInfo {
    PercentileMethod percentile_method = PercentileMethod::LINEAR_INTERPOLATION;
    core::ExecutionPolicy policy = core::ExecutionPolicy::NONE;
  };

  class Analyzer {
  public:
    Analyzer(const Analyzer&) = delete;
    Analyzer& operator=(const Analyzer&) = delete;

    static std::unique_ptr<Analyzer> create(const AnalysisCreateInfo& create_info);

    // ---

    double mean(const std::vector<double>& data) const;

    double stddev(const std::vector<double>& data) const;

  private:
    explicit Analyzer(const AnalysisCreateInfo& createInfo);

    core::ExecutionPolicy m_policy;
    PercentileMethod m_percentileMethod;
  };

}// namespace Analysis

}
