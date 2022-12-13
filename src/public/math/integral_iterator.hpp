
#pragma once

#include "math/infinity.hpp"
#include <type_traits>

namespace math {
template <typename Number>
  requires(std::is_integral_v<Number> && std::is_signed_v<Number>)
struct integral_iterator {
  // TODO: Add three way compare assertions for add and subtract functions!

  using value_type = Number;
  using difference_type = value_type;
  using iterator_category = std::contiguous_iterator_tag;

  value_type current;

  constexpr integral_iterator &operator++() {
    assert(current != std::numeric_limits<value_type>::max());
    ++current;
    return *this;
  }

  constexpr integral_iterator operator++(int) {
    integral_iterator copy{*this};
    operator++();
    return copy;
  }

  constexpr integral_iterator &operator--() {
    assert(current != std::numeric_limits<value_type>::min());
    --current;
    return *this;
  }

  constexpr integral_iterator operator--(int)
    requires std::is_signed_v<value_type>
  {
    integral_iterator copy{*this};
    operator--();
    return copy;
  }

  constexpr integral_iterator &operator+=(difference_type increment) {
    current += increment;
    return *this;
  }

  constexpr integral_iterator &operator-=(difference_type decrement) {
    current -= decrement;
    return *this;
  }

  constexpr value_type operator*() const { return current; }

  constexpr value_type operator[](value_type index) const {
    return current += index;
  }

  friend constexpr bool operator==(const integral_iterator &left,
                                   const integral_iterator &right) = default;

  friend constexpr auto operator<=>(const integral_iterator &left,
                                    const integral_iterator &right) = default;

  friend constexpr bool operator==(integral_iterator, infinity_type) {
    return false;
  }

  friend constexpr difference_type operator-(const integral_iterator &left,
                                             const integral_iterator &right) {
    return left.current - right.current;
  }

  friend constexpr integral_iterator operator+(integral_iterator iterator,
                                               value_type increment) {
    iterator += increment;
    return iterator;
  }

  friend constexpr infinity_type operator-(integral_iterator, infinity_type) {
    return {};
  }

  friend constexpr integral_iterator operator-(integral_iterator iterator,
                                               difference_type decrement) {
    iterator -= decrement;
    return iterator;
  }

  friend constexpr integral_iterator operator+(value_type increment,
                                               integral_iterator iterator) {
    return iterator + increment;
  }
};
} // namespace math
