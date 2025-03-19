#include <sstream>
#include <string>
#include <vector>
#include <random>

#include "vector_lib.h"
#include "point.h"

namespace t_utils{

  unsigned count_ocr(std::string str, std::string sub);
  bool is_sub_str(std::string str, std::string sub);
  template <size_t DIM> Vector<DIM> genRandVector(
      std::mt19937& gen,
      std::uniform_real_distribution<>& dis
  ){
    Point<DIM> p;
    for (size_t i = 0; i < DIM; i++)
      p[i] = dis(gen);
    return Vector<DIM>(p);
  }
}
