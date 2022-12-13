
#pragma once

#include "math/numberspaces.hpp"
#include "math/set/empty.hpp"
#include "math/set/set.hpp"
#include <limits>
#include <type_traits>

namespace math {
template <typename Number>
  requires(std::is_integral_v<Number>)
struct integral_iterator {
  using value_type = Number;
  using difference_type = Number;
  using iterator_category = std::contiguous_iterator_tag;

  value_type current;

  constexpr integral_iterator &operator++() {
    ++current;
    return *this;
  }

  constexpr integral_iterator operator++(int) {
    integral_iterator copy{*this};
    operator++();
    return copy;
  }

  constexpr integral_iterator &operator--() {
    --current;
    return *this;
  }

  constexpr integral_iterator operator--(int) {
    integral_iterator copy{*this};
    operator--();
    return copy;
  }

  constexpr integral_iterator &operator+=(Number increment) {
    current += increment;
    return *this;
  }

  constexpr integral_iterator &operator-=(Number decrement) {
    current -= decrement;
    return *this;
  }

  constexpr value_type operator*() const { return current; }

  constexpr value_type operator[](value_type index) const {
    return current += index;
  }

  friend auto operator<=>(const integral_iterator &,
                          const integral_iterator &) = default;
  friend value_type operator-(const integral_iterator &left,
                              const integral_iterator &right) {
    return left.current - right.current;
  }

  friend integral_iterator operator+(integral_iterator iterator,
                                     value_type increment) {
    iterator += increment;
    return iterator;
  }

  friend integral_iterator operator-(integral_iterator iterator,
                                     value_type decrement) {
    iterator -= decrement;
    return iterator;
  }

  friend constexpr integral_iterator operator+(value_type increment,
                                               integral_iterator iterator) {
    return iterator + increment;
  }
};

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

  // Methods.
  constexpr auto contains(const auto &value) const noexcept -> bool {
    if constexpr (set::is_empty_set<decltype(value)>) {
      return true;
    } else if constexpr (!std::three_way_comparable_with<decltype(value),
                                                         number_type>) {
      return false;
    } else {
      bool lower_bound = value >= low;
      bool upper_bound = value < high;
      return lower_bound && upper_bound;
    }
  }

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

// TODO: Custom checks for numberspaces to save time.

} // namespace set
} // namespace math
