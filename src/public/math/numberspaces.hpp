
#pragma once

#include <cmath>
#include <math/set/empty.hpp>
#include <type_traits>

using math::set::is_empty_set;

namespace math {
namespace numberspaces {

struct natural_type {
  template <typename Value> static constexpr bool contains(const Value &value) {
    if constexpr (is_empty_set<Value>) {
      return true;
    } else if constexpr (std::is_integral_v<Value>) {
      return value >= Value{1};
    } else if constexpr (std::is_floating_point_v<Value>) {
      return (value >= Value{1.0}) && (fmod(value, Value{1.0}) == 0);
    } else {
      return false;
    }
  }
};
constexpr natural_type natural{};

struct whole_type : natural_type {
  template <typename Value> static constexpr bool contains(const Value &value) {
    if constexpr (is_empty_set<Value>) {
      return true;
    } else if constexpr (std::is_integral_v<Value>) {
      return value >= Value{0};
    } else if constexpr (std::is_floating_point_v<Value>) {
      return (value >= Value{0.0}) && (fmod(value, Value{1.0}) == 0);
    } else {
      return false;
    }
  }
};
constexpr whole_type whole{};

struct integer_type : whole_type {
  template <typename Value> static constexpr bool contains(const Value &value) {
    if constexpr (is_empty_set<Value> || std::is_integral_v<Value>) {
      return true;
    } else if constexpr (std::is_floating_point_v<Value>) {
      return fmod(value, Value{1.0}) == Value{0};
    } else {
      return false;
    }
  }
};
constexpr integer_type integer{};

struct real_type : integer_type {
  template <typename Value>
  static constexpr bool contains(const Value &value) noexcept {
    if constexpr (is_empty_set<Value> || std::is_integral_v<Value> ||
                  std::is_floating_point_v<Value>) {
      return true;
    } else {
      return false;
    }
  }
};
constexpr real_type real{};

} // namespace numberspaces
} // namespace math
