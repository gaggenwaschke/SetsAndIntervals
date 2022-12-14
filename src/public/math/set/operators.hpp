
#pragma once

#include "math/operations.hpp"
#include "math/set/element_of.hpp"
#include "math/set/flattening_view.hpp"
#include <ranges>

// Conjunction

constexpr auto operator&(const math::set::set auto &left,
                         const math::set::set auto &right) {
  if constexpr (math::set::is_empty_set<decltype(left)> ||
                math::set::is_empty_set<decltype(right)>) {
    return math::set::empty{};
  } else {
    return math::set::flattening_view{math::operations::conjunction, left,
                                      right};
  }
}

// Disjunction

constexpr auto operator|(math::set::set auto &left,
                         math::set::set auto &right) {
  if constexpr (math::set::is_empty_set<decltype(left)>) {
    return right;
  } else if constexpr (math::set::is_empty_set<decltype(right)>) {
    return left;
  } else {
    return math::set::flattening_view{math::operations::disjunction, left,
                                      right};
  }
}

// Symmetric Difference

constexpr auto operator^(math::set::set auto &left,
                         math::set::set auto &right) {
  if constexpr (math::set::is_empty_set<decltype(left)>) {
    return right;
  } else if constexpr (math::set::is_empty_set<decltype(right)>) {
    return left;
  } else {
    return math::set::flattening_view{math::operations::symmetric_difference,
                                      left, right};
  }
}