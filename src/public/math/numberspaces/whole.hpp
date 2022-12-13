#pragma once

#include "math/infinity.hpp"
#include "math/integral_iterator.hpp"
#include "math/numberspaces/natural.hpp"
#include "math/set/set.hpp"

namespace math {
namespace numberspaces {
struct whole_type : natural_type {
  constexpr integral_iterator<std::int64_t> begin() const { return {0}; }
  constexpr infinity_type end() const { return {}; }
};
constexpr whole_type whole{};
} // namespace numberspaces

namespace set {
template <typename Number>
  requires(std::is_integral_v<Number> && std::is_unsigned_v<Number>)
struct custom_is_element_of<Number, numberspaces::whole_type> {
  constexpr std::true_type operator()(Number number,
                                      numberspaces::whole_type) const {
    return {};
  }
};

template <typename Number>
  requires(std::is_integral_v<Number> && std::is_signed_v<Number>)
struct custom_is_element_of<Number, numberspaces::whole_type> {
  constexpr bool operator()(Number number, numberspaces::whole_type) const {
    return number >= Number{0};
  }
};

template <typename Number>
  requires std::is_floating_point_v<Number>
struct custom_is_element_of<Number, numberspaces::whole_type> {
  constexpr bool operator()(Number number, numberspaces::whole_type) const {
    return (number >= Number{0}) && (fmod(number, Number{1}) == 0);
  }
};
} // namespace set
} // namespace math
