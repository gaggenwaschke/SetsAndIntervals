
#pragma once

#include <cmath>
#include <math/set/empty.hpp>
#include <type_traits>

namespace math::set::number {

struct natural {
  constexpr auto contains(const auto &value) const -> bool {
    using value_type = std::remove_cvref_t<decltype(value)>;

    if constexpr (is_empty_set<value_type>) {
      return true;
    } else if constexpr (std::is_integral_v<value_type>) {
      return value >= value_type{1};
    } else if constexpr (std::is_floating_point_v<value_type>) {
      return (value >= value_type{1.0}) && (fmod(value, value_type{1.0}) == 0);
    } else {
      return false;
    }
  }
};

struct whole {
  constexpr auto contains(const auto &value) const -> bool {
    using value_type = std::remove_cvref_t<decltype(value)>;

    if constexpr (is_empty_set<value_type>) {
      return true;
    } else if constexpr (std::is_integral_v<value_type>) {
      return value >= value_type{0};
    } else if constexpr (std::is_floating_point_v<value_type>) {
      return (value >= value_type{0.0}) && (fmod(value, value_type{1.0}) == 0);
    } else {
      return false;
    }
  }
};

struct integers {
  constexpr auto contains(const auto &value) const -> bool {
    using value_type = std::remove_cvref_t<decltype(value)>;

    if constexpr (is_empty_set<value_type>) {
      return true;
    } else if constexpr (std::is_integral_v<value_type>) {
      return true;
    } else if constexpr (std::is_floating_point_v<value_type>) {
      return fmod(value, value_type{1.0}) == 0;
    } else {
      return false;
    }
  }
};

struct real {
  constexpr auto contains(const auto &value) const noexcept -> bool {
    using value_type = std::remove_cvref_t<decltype(value)>;

    if constexpr (is_empty_set<value_type>) {
      return true;
    } else if constexpr (std::is_integral_v<value_type> ||
                         std::is_floating_point_v<value_type>) {
      return true;
    } else {
      return false;
    }
  }
};

} // namespace math::set::number
