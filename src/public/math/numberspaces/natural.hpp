#pragma once

#include "math/infinity.hpp"
#include "math/integral_iterator.hpp"
#include "math/set.hpp"

namespace math {
namespace numberspaces {
struct natural_type {
  constexpr integral_iterator<std::int64_t> begin() const { return {1}; }
  constexpr infinity_type end() const { return {}; }
};
constexpr natural_type natural{};
} // namespace numberspaces

namespace set {
template <typename Number>
  requires std::is_integral_v<Number>
struct custom_is_element_of<Number, numberspaces::natural_type> {
  constexpr bool operator()(Number number, numberspaces::natural_type) const {
    return number >= Number{1};
  }
};

template <typename Number>
  requires std::is_floating_point_v<Number>
struct custom_is_element_of<Number, numberspaces::natural_type> {
  constexpr bool operator()(Number number, numberspaces::natural_type) const {
    return (number >= Number{1}) && (fmod(number, Number{1}) == Number{0});
  }
};
} // namespace set
} // namespace math
