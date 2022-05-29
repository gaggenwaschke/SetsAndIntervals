
#pragma once

#include <math/set/set.hpp>

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
} // namespace math::set
