#pragma once

#include <cstddef>
#include <cstdint>

namespace MATH_LIB {

enum class DetAlgorithm {
  // Uses the classic cofactor expansion.
  // Recommended for small matrices (<= 3x3) due to its O(n!) complexity.
  COFACTOR_EXPANSION,

  // Uses LU Decomposition to find the determinant.
  // Much more efficient for larger matrices, typically O(n^3).
  // This is generally the default and recommended choice.
  LU_DECOMPOSITION
};

enum class CalcOptions : std::uint32_t {
  NONE = 0,
  PARALLELIZE = 1 << 0,
  OPTIMIZATIONS = 1 << 1,
  GPU_ACCELERATION = 1 << 2
};

typedef struct {
  DetAlgorithm detAlgorithm;
  CalcOptions options;
} MatrixConfig;

}
