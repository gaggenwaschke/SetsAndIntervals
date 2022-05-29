
#pragma once

#include <concepts>
#include <math/interval.hpp>
#include <ranges>
#include <tuple>

namespace math::set {
// TODO: empty set

/**
 * @brief Check whether a value is contained in a range.
 */
constexpr auto contains(const std::ranges::range auto &range, const auto &value)
    -> bool;

template <typename Number, bool InclusiveLow, bool InclusiveHigh>
constexpr auto
contains(const interval<Number, InclusiveLow, InclusiveHigh> &interval) -> bool;

template <typename... Elements>
constexpr auto contains(const std::tuple<Elements...> &tuple) -> bool;
} // namespace math::set

// ---
// Implementation
// ---

namespace math::set {
// Ranges
constexpr auto contains(const std::ranges::range auto &range, const auto &value)
    -> bool requires(
        !std::equality_comparable_with<
            decltype(value), std::ranges::range_value_t<decltype(range)>>) {
  return false;
}

constexpr auto contains(const std::ranges::range auto &range, const auto &value)
    -> bool requires(
        std::equality_comparable_with<
            decltype(value), std::ranges::range_value_t<decltype(range)>>) {
  return std::ranges::find(range, value) != std::cend(range);
}

// Intervals
template <typename Number, bool InclusiveLow, bool InclusiveHigh>
constexpr auto
contains(const interval<Number, InclusiveLow, InclusiveHigh> &interval,
         const auto &number) -> bool {
  return interval.contains(number);
}

// Tuples
constexpr auto tuple_element_equals_any(const auto &element, const auto &value)
    -> bool requires(
        !std::equality_comparable_with<decltype(element), decltype(value)>) {
  return false;
}

constexpr auto tuple_element_equals_any(const auto &element, const auto &value)
    -> bool requires(
        std::equality_comparable_with<decltype(element), decltype(value)>) {
  return element == value;
}

template <typename... Elements>
constexpr auto contains(const std::tuple<Elements...> &tuple, const auto &value)
    -> bool {
  return std::apply(
      [&value](const auto &...element) {
        return (tuple_element_equals_any(element, value) || ...);
      },
      tuple);
}
} // namespace math::set
