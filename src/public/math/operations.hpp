
#pragma once

namespace math::operations {
struct conjunction_type {
  constexpr bool operator()(const auto &...args) { return (args && ...); };
  constexpr static bool neutral_element{true};
};
constexpr conjunction_type conjunction{};

struct disjunction_type {
  constexpr bool operator()(const auto &...args) { return (args || ...); };
  constexpr static bool neutral_element{false};
};
constexpr disjunction_type disjunction{};

struct symmetric_difference_type {
  constexpr bool operator()(const auto &...args) { return (args ^ ...); }
};
constexpr symmetric_difference_type symmetric_difference{};
} // namespace math::operations
