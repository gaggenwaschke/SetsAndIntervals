
#pragma once

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

  constexpr interval(Number low, Number high) noexcept;

  // Methods.
  constexpr auto contains(const auto &value) const -> bool requires(
      !std::three_way_comparable_with<decltype(value), number_type>) {
    return false;
  }

  constexpr auto contains(const auto &value) const -> bool requires(
      std::three_way_comparable_with<decltype(value), number_type>) {
    bool lower_bound = InclusiveLow ? (value >= low) : (value > low);
    bool upper_bound = InclusiveHigh ? (value <= high) : (value < high);
    return lower_bound && upper_bound;
  }

  // Members.
  Number low;
  Number high;
};
} // namespace math

// ---
// Implementation
// ---

namespace math {
template <typename Number, bool InclusiveLow, bool InclusiveHigh>
constexpr interval<Number, InclusiveLow, InclusiveHigh>::interval(
    Number low, Number high) noexcept
    : low{low}, high{high} {}
} // namespace math
