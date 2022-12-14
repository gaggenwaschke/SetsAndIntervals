
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

// Standard operator overloads.
// These conserve as much information about bool operations as possible
// for compile time operations.

constexpr std::true_type operator||(std::true_type, std::true_type) {
  return {};
}

constexpr std::true_type operator||(std::false_type, std::true_type) {
  return {};
}

constexpr std::true_type operator||(std::true_type, std::false_type) {
  return {};
}

constexpr std::false_type operator||(std::false_type, std::false_type) {
  return {};
}

constexpr std::true_type operator||(std::true_type, bool) { return {}; }
constexpr std::true_type operator||(bool, std::true_type) { return {}; }

constexpr std::true_type operator&&(std::true_type, std::true_type) {
  return {};
}

constexpr std::false_type operator&&(std::false_type, std::true_type) {
  return {};
}

constexpr std::false_type operator&&(std::true_type, std::false_type) {
  return {};
}

constexpr std::false_type operator&&(std::false_type, std::false_type) {
  return {};
}

constexpr std::false_type operator&&(std::false_type, bool) { return {}; }
constexpr std::false_type operator&&(bool, std::false_type) { return {}; }

constexpr std::false_type operator^(std::true_type, std::true_type) {
  return {};
}

constexpr std::true_type operator^(std::false_type, std::true_type) {
  return {};
}

constexpr std::true_type operator^(std::true_type, std::false_type) {
  return {};
}

constexpr std::false_type operator^(std::false_type, std::false_type) {
  return {};
}
