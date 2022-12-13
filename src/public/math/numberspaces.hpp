
#pragma once

#include "math/set/empty.hpp"
#include "math/set/set.hpp"
#include <cmath>
#include <type_traits>

using math::set::is_empty_set;

namespace math {
namespace numberspaces {

struct natural_type {};
constexpr natural_type natural{};

struct whole_type : natural_type {};
constexpr whole_type whole{};

struct integer_type : whole_type {};
constexpr integer_type integer{};

struct real_type : integer_type {};
constexpr real_type real{};

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

template <typename Number>
  requires(std::is_integral_v<Number> && std::is_unsigned_v<Number>)
struct custom_is_element_of<Number, numberspaces::whole_type> {
  constexpr bool operator()(Number number, numberspaces::whole_type) const {
    return true;
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

template <typename Number>
  requires std::is_integral_v<Number>
struct custom_is_element_of<Number, numberspaces::integer_type> {
  constexpr bool operator()(Number number, numberspaces::integer_type) const {
    return true;
  }
};

template <typename Number>
  requires std::is_floating_point_v<Number>
struct custom_is_element_of<Number, numberspaces::integer_type> {
  constexpr bool operator()(Number number, numberspaces::integer_type) const {
    return fmod(number, Number{1}) == 0;
  }
};

template <typename Number>
  requires(std::is_integral_v<Number> || std::is_floating_point_v<Number>)
struct custom_is_element_of<Number, numberspaces::real_type> {
  constexpr bool operator()(Number number, numberspaces::real_type) const {
    return true;
  }
};
} // namespace set
} // namespace math
