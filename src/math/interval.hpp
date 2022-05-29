
#pragma once

#include <math/set/empty.hpp>
#include <math/set/set.hpp>

namespace math {
template <typename Number, bool InclusiveLow = true, bool InclusiveHigh = false>
struct interval {
  // Types.
  using number_type = Number;

  // Constructors.
  interval() = delete;
  constexpr interval(const interval &) noexcept = default;
  constexpr interval(interval &&) noexcept = default;
  constexpr interval &operator=(const interval &) noexcept = default;
  constexpr interval &operator=(interval &&) noexcept = default;

  constexpr interval(Number low, Number high) noexcept : low{low}, high{high} {
    static_assert(::math::set::set<interval>,
                  "math::interval must work as set.");
  }

  // Methods.
  constexpr auto contains(const auto &value) const noexcept -> bool {
    if constexpr (set::is_empty_set<decltype(value)>) {
      return true;
    } else if constexpr (!std::three_way_comparable_with<decltype(value),
                                                         number_type>) {
      return false;
    } else {
      bool lower_bound = InclusiveLow ? (value >= low) : (value > low);
      bool upper_bound = InclusiveHigh ? (value <= high) : (value < high);
      return lower_bound && upper_bound;
    }
  }

  // Members.
  Number low;
  Number high;
};
} // namespace math
