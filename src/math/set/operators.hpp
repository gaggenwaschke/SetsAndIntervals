
#pragma once

#include <math/set/set.hpp>
#include <ranges>

namespace math::set {

// Conjunction

constexpr auto operator&(const set auto &left, empty) -> empty { return {}; }
constexpr auto operator&(empty, const set auto &right) -> empty
    requires(!is_empty_set<decltype(right)>) {
  return {};
}

// Disjunction

constexpr auto &operator|(set auto &left, empty) { return left; }
constexpr auto &
operator|(empty, set auto &right) requires(!is_empty_set<decltype(right)>) {
  return right;
}

constexpr auto operator|(set auto &left, set auto &right) requires(
    std::ranges::range<decltype(left)> &&std::ranges::range<decltype(right)>) {
  using left_value_type = std::ranges::range_value_t<decltype(left)>;
  using right_value_type = std::ranges::range_value_t<decltype(right)>;
}
} // namespace math::set
