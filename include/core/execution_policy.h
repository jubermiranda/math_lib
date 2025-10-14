#pragma once

#include <cstdint>

namespace math_lib::core {

enum class ExecutionPolicy : std::uint32_t {
  NONE = 0,
  PARALLELIZE = 1 << 0,
  OPTIMIZATIONS = 1 << 1,
  GPU_ACCELERATION = 1 << 2
};

}
