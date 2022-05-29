
#pragma once

#include <math/set/flattening_view.hpp>
#include <math/set/set.hpp>
#include <ranges>

// Conjunction

constexpr auto operator&(const math::set::set auto &left,
                         const math::set::set auto &right) {
  if constexpr (math::set::is_empty_set<decltype(left)> ||
                math::set::is_empty_set<decltype(right)>) {
    return math::set::empty{};
  } else {
    return math::set::flattening_view{math::set::conjunction{}, left, right};
  }
}

// Disjunction

constexpr auto operator|(math::set::set auto &left,
                         math::set::set auto &right) noexcept {
  if constexpr (math::set::is_empty_set<decltype(left)>) {
    return right;
  } else if constexpr (math::set::is_empty_set<decltype(right)>) {
    return left;
  } else {
    return math::set::flattening_view{math::set::disjunction{}, left, right};
  }
}