
#pragma once

#include <type_traits>

namespace math::operations {
struct conjunction_type {
  constexpr auto operator()(const auto &...args) const {
    return (args && ...);
  };
  constexpr static std::true_type neutral_element{};
};
constexpr conjunction_type conjunction{};

struct disjunction_type {
  constexpr auto operator()(const auto &...args) const {
    return (args || ...);
  };
  constexpr static std::false_type neutral_element{};
};
constexpr disjunction_type disjunction{};

struct symmetric_difference_type {
  constexpr auto operator()(const auto &...args) const { return (args ^ ...); }
};
constexpr symmetric_difference_type symmetric_difference{};
} // namespace math::operations
