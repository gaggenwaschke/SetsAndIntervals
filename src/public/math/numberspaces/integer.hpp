#pragma once

#include "math/infinity.hpp"
#include "math/integral_iterator.hpp"
#include "math/numberspaces/whole.hpp"
#include "math/set.hpp"

namespace math {
namespace numberspaces {
struct integer_type : whole_type {
  constexpr integral_iterator<std::int64_t> begin() const { return {1}; }
  constexpr infinity_type end() const { return {}; }
};
constexpr integer_type integer{};
} // namespace numberspaces

namespace set {
template <typename Number>
  requires std::is_integral_v<Number>
struct custom_is_element_of<Number, numberspaces::integer_type> {
  constexpr std::true_type operator()(Number number,
                                      numberspaces::integer_type) const {
    return {};
  }
};

template <typename Number>
  requires std::is_floating_point_v<Number>
struct custom_is_element_of<Number, numberspaces::integer_type> {
  constexpr bool operator()(Number number, numberspaces::integer_type) const {
    return fmod(number, Number{1}) == 0;
  }
};
} // namespace set
} // namespace math
