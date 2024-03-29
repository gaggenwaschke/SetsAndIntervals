#pragma once

#include "math/infinity.hpp"
#include "math/integral_iterator.hpp"
#include "math/numberspaces/integer.hpp"
#include "math/set.hpp"

namespace math {
namespace numberspaces {
struct real_type {};
constexpr real_type real{};
} // namespace numberspaces

namespace set {
template <> struct custom_cardinality<numberspaces::real_type> {
  constexpr auto operator()(numberspaces::real_type) const { return infinity; }
};

template <typename Number>
  requires(std::is_integral_v<Number> || std::is_floating_point_v<Number>)
struct custom_is_element_of<Number, numberspaces::real_type> {
  constexpr std::true_type operator()(Number number,
                                      numberspaces::real_type) const {
    return {};
  }
};

template <typename Set>
  requires std::is_base_of_v<Set, numberspaces::integer_type>
struct custom_is_subset_of<Set, numberspaces::real_type> {
  constexpr std::true_type operator()(Set, numberspaces::real_type) const {
    return {};
  }
};
} // namespace set
} // namespace math
