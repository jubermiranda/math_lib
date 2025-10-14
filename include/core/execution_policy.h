#pragma once

#include <cstdint>

namespace MathLib::Core {

enum class ExecutionPolicy : std::uint32_t {
  NONE = 0,
  PARALLELIZE = 1 << 0,
  OPTIMIZATIONS = 1 << 1,
  GPU_ACCELERATION = 1 << 2
};

}
