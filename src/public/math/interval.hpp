
#pragma once

#include "math/integral_iterator.hpp"
#include "math/numberspaces.hpp"
#include "math/set/empty.hpp"
#include "math/set/set.hpp"
#include <limits>
#include <type_traits>

namespace math {
template <typename Number>
  requires(std::is_integral_v<Number> || std::is_floating_point_v<Number>)
struct interval {
  // Types.
  using number_type = Number;

  // Constructors.
  interval() = delete;
  constexpr interval(const interval &) noexcept = default;
  constexpr interval(interval &&) noexcept = default;
  constexpr interval &operator=(const interval &) noexcept = default;
  constexpr interval &operator=(interval &&) noexcept = default;

  constexpr interval(Number low = std::numeric_limits<Number>::min(),
                     Number high = std::numeric_limits<Number>::max()) noexcept
      : low{low}, high{high} {}

  constexpr auto begin() const
    requires std::is_integral_v<number_type>
  {
    return integral_iterator<number_type>{low};
  }
  constexpr auto end() const
    requires std::is_integral_v<number_type>
  {
    return integral_iterator<number_type>{high};
  }

  // Members.
  Number low;
  Number high;
};

namespace set {
template <typename NumberLeft, typename NumberRight>
struct custom_subset_check<interval<NumberLeft>, interval<NumberRight>> {
  constexpr bool operator()(const interval<NumberLeft> &left,
                            const interval<NumberRight> &right) const {
    return left.low >= right.low && left.high <= right.high;
  }
};

template <typename Number>
  requires std::is_integral_v<Number>
struct custom_subset_check<interval<Number>, numberspaces::natural_type> {
  constexpr bool operator()(const interval<Number> &interval,
                            numberspaces::natural_type natural) const {
    return set::is_element_of(interval.low, natural);
  }
};

template <typename Number>
  requires std::is_floating_point_v<Number>
struct custom_subset_check<interval<Number>, numberspaces::natural_type> {
  constexpr bool operator()(const interval<Number> &interval,
                            numberspaces::natural_type natural) const {
    return (interval.low == interval.high) &&
           set::is_element_of(natural, interval.low);
  }
};

template <typename Number>
  requires(std::is_integral_v<Number> && std::is_unsigned_v<Number>)
struct custom_subset_check<interval<Number>, numberspaces::whole_type> {
  constexpr std::true_type operator()(const interval<Number> &interval,
                                      numberspaces::whole_type) const {
    return {};
  }
};

template <typename Number>
  requires(std::is_integral_v<Number> && std::is_signed_v<Number>)
struct custom_subset_check<interval<Number>, numberspaces::whole_type> {
  constexpr bool operator()(const interval<Number> &interval,
                            numberspaces::whole_type whole) const {
    return set::is_element_of(interval.low, whole);
  }
};

template <typename Number>
  requires std::is_floating_point_v<Number>
struct custom_subset_check<interval<Number>, numberspaces::whole_type> {
  constexpr bool operator()(const interval<Number> &interval,
                            numberspaces::whole_type whole) const

  {
    return (interval.low == interval.high) &&
           set::is_element_of(interval.low, whole);
  }
};

template <typename Number>
  requires std::is_integral_v<Number>
struct custom_subset_check<interval<Number>, numberspaces::integer_type> {
  constexpr std::true_type operator()(const interval<Number> &interval,
                                      numberspaces::whole_type) const {
    return {};
  }
};

template <typename Number>
  requires std::is_floating_point_v<Number>
struct custom_subset_check<interval<Number>, numberspaces::integer_type> {
  constexpr bool operator()(const interval<Number> &interval,
                            numberspaces::integer_type integer) const {
    return (interval.low == interval.high) &&
           set::is_element_of(integer, interval.low);
  }
};

template <typename Number>
struct custom_subset_check<interval<Number>, numberspaces::real_type> {
  constexpr std::true_type operator()(const interval<Number> &interval,
                                      numberspaces::real_type real) const {
    return {};
  }
};
} // namespace set
} // namespace math
