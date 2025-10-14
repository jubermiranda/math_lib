#pragma once

#include "core/execution_policy.h"

namespace math_lib::matrix {

enum class DetAlgorithm {
  // Uses the classic cofactor expansion.
  // Recommended for small matrices (<= 3x3) due to its O(n!) complexity.
  COFACTOR_EXPANSION,

  // Uses LU Decomposition to find the determinant.
  // Much more efficient for larger matrices, typically O(n^3).
  // This is generally the default and recommended choice.
  LU_DECOMPOSITION
};

typedef struct {
  DetAlgorithm detAlgorithm;
  math_lib::core::ExecutionPolicy options;
} MatrixCreateInfo;

}
