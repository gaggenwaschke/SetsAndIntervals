#pragma once

namespace math {
struct infinity_type {
  friend constexpr std::true_type operator==(infinity_type, infinity_type) {
    return {};
  }
};

constexpr infinity_type infinity{};
} // namespace math
