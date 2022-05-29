
#pragma once

#include <array>
#include <concepts>
#include <math/interval.hpp>
#include <math/set/empty.hpp>
#include <ranges>
#include <tuple>

namespace math::set {
// Empty set
constexpr auto contains(const auto &any_set, const auto &value)
    -> bool requires(is_empty_set<decltype(value)>) {
  return true;
}

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

template <typename Candidate>
concept set = is_empty_set<Candidate> || requires(const Candidate &candidate) {
  { contains(candidate, empty{}) } -> std::same_as<bool>;
  { contains(candidate, int{1}) } -> std::same_as<bool>;
};

// Static assertions.
static_assert(set<std::array<int, 3>>, "Array must work as a set.");
static_assert(set<std::vector<int>>, "Vector must work as a set.");
static_assert(set<std::tuple<int, char>>, "Tuple must work as a set.");
static_assert(set<interval<int>>, "math::interval must work as a set.");
static_assert(set<empty>, "math::set::empty must work as set.");
} // namespace math::set