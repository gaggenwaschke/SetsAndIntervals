
#pragma once

#include <concepts>
#include <math/interval.hpp>
#include <math/set/empty.hpp>
#include <ranges>
#include <tuple>

namespace math::set {
constexpr auto contains(const auto &any_set, empty) -> bool;

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

// Empty set
constexpr auto contains(const auto &any_set, empty) -> bool { return true; }

// Ranges
constexpr auto contains(const std::ranges::range auto &range, const auto &value)
    -> bool requires(
        !is_empty_set<decltype(value)> &&
        !std::equality_comparable_with<
            decltype(value), std::ranges::range_value_t<decltype(range)>>) {
  return false;
}

constexpr auto contains(const std::ranges::range auto &range, const auto &value)
    -> bool requires(
        !is_empty_set<decltype(value)> &&
        std::equality_comparable_with<
            decltype(value), std::ranges::range_value_t<decltype(range)>>) {
  return std::ranges::find(range, value) != std::cend(range);
}

// Intervals
template <typename Number, bool InclusiveLow, bool InclusiveHigh>
constexpr auto
contains(const interval<Number, InclusiveLow, InclusiveHigh> &interval,
         const auto &value) -> bool requires(!is_empty_set<decltype(value)>) {
  return interval.contains(value);
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
    -> bool requires(!is_empty_set<decltype(value)>) {
  return std::apply(
      [&value](const auto &...element) {
        return (tuple_element_equals_any(element, value) || ...);
      },
      tuple);
}
} // namespace math::set
