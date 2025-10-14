#pragma once

#include <cstddef>
#include <random>
#include <vector>

namespace MathLib {
namespace Rand {
  class RandomProvider {
    private:
      std::mt19937 m_gen;
    public:
      explicit RandomProvider(unsigned int seed) : m_gen(seed) {}

      std::mt19937& gen() { return m_gen; }
  };
}

namespace Dist {
  double exp(Rand::RandomProvider& rand, double mean);
  double norm(Rand::RandomProvider& rand, double mean, double stddev);
  double triang(Rand::RandomProvider& rand, double min, double mode, double max);
  double uniform(Rand::RandomProvider& rand, double min, double max);
  int uniform_int(Rand::RandomProvider& rand, int min, int max);
  size_t weighted(Rand::RandomProvider& rand, std::vector<double> weights);
  double lognorm(Rand::RandomProvider& rand, double mean, double stddev);
}


}
