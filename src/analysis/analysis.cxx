#include "analysis/analysis.h"
#include <stdexcept>

namespace math_lib {

  double dist::exp(rand::RandomProvider& rand, double mean)
  {
    throw std::runtime_error("not impl");
  }

  double dist::norm(rand::RandomProvider& rand, double mean, double stddev)
  {
    throw std::runtime_error("not impl");
  }

  double dist::triangular(rand::RandomProvider& rand, double min, double mode, double max)
  {
    throw std::runtime_error("not impl");
  }

  double dist::uniform(rand::RandomProvider& rand, double min, double max)
  {
    throw std::runtime_error("not impl");
  }

  int dist::uniform_int(rand::RandomProvider& rand, int min, int max)
  {
    throw std::runtime_error("not impl");
  }

  size_t dist::weighted_discrete(rand::RandomProvider& rand, const std::vector<double>& weights)
  {
    throw std::runtime_error("not impl");
  }

  double dist::lognorm(rand::RandomProvider& rand, double mean, double stddev)
  {
    throw std::runtime_error("not impl");
  }

namespace analysis{

  Analyzer::Analyzer(const AnalysisCreateInfo& info) :
      m_percentile_method(info.percentile_method),
      m_policy(info.policy)
  {
    throw std::runtime_error("not impl");
  }

  std::unique_ptr<Analyzer> Analyzer::create(const AnalysisCreateInfo& create_info)
  {
    throw std::runtime_error("not impl");
  }

  double Analyzer::mean(const std::vector<double>& data) const
  {
    throw std::runtime_error("not impl");
  }

  double Analyzer::stddev(const std::vector<double>& data) const
  {
    throw std::runtime_error("not impl");
  }

}// namespace Analysis

}// namespace math_lib


