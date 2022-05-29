
#pragma once

#include <array>
#include <concepts>
#include <math/set/empty.hpp>
#include <ranges>
#include <tuple>

namespace math::set {

template <typename Set>
concept set_members = requires(const Set &set) {
  { set.contains(empty{}) } -> std::same_as<bool>;
  { set.template contains<int>(1) } -> std::same_as<bool>;
};

// Empty set
constexpr auto contains(const auto &any_set, const auto &value) noexcept
    -> bool requires(is_empty_set<decltype(value)>) {
  return true;
}

// Ranges
constexpr auto contains(const std::ranges::range auto &range,
                        const auto &value) noexcept
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

// Tuples
constexpr auto tuple_element_equals_any(const auto &element,
                                        const auto &value) noexcept
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

// Data types that supply their own "contains" implementation.
constexpr auto contains(const set_members auto &set, const auto &value)
    -> bool requires(!is_empty_set<decltype(value)>) {
  return set.template contains<decltype(value)>(value);
}

template <typename Candidate>
concept set = is_empty_set<Candidate> || requires(const Candidate &candidate) {
  { ::math::set::contains(candidate, empty{}) } -> std::same_as<bool>;
  { ::math::set::contains(candidate, int{1}) } -> std::same_as<bool>;
};

// Static assertions.
static_assert(set<std::array<int, 3>>, "Array must work as a set.");
static_assert(set<std::vector<int>>, "Vector must work as a set.");
static_assert(set<std::tuple<int, char>>, "Tuple must work as a set.");
static_assert(set<empty>, "math::set::empty must work as set.");
} // namespace math::set