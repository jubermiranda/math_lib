#pragma once

#include <cstddef>

namespace ML_ETC {

enum class DetCalcType {
  // Uses the classic cofactor expansion.
  // Recommended for small matrices (<= 3x3) due to its O(n!) complexity.
  COFACTOR_EXPANSION,

  // Uses LU Decomposition to find the determinant.
  // Much more efficient for larger matrices, typically O(n^3).
  // This is generally the default and recommended choice.
  LU_DECOMPOSITION
};

typedef struct {
  size_t row_len;
  size_t col_len;


} MATRIX_CONFIG;

}
