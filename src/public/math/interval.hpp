
#pragma once

#include <math/set/empty.hpp>
#include <math/set/set.hpp>

#include <limits>

namespace math {
template <typename Number, bool InclusiveLow = true, bool InclusiveHigh = false>
struct interval {
  // Types.
  using number_type = Number;

  // Assertions.
  static_assert(::math::set::set<interval>, "math::interval must work as set.");

  // Constructors.
  interval() = delete;
  constexpr interval(const interval &) noexcept = default;
  constexpr interval(interval &&) noexcept = default;
  constexpr interval &operator=(const interval &) noexcept = default;
  constexpr interval &operator=(interval &&) noexcept = default;

  constexpr interval(Number low = std::numeric_limits<Number>::min(),
                     Number high = std::numeric_limits<Number>::max()) noexcept
      : low{low}, high{high} {}

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

static_assert(set::set<interval<int>>, "Interval must be a set!");
} // namespace math
