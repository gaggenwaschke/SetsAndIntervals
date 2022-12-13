#pragma once

#include "math/set/empty.hpp"
#include "math/type_traits.hpp"
#include <ranges>

namespace math::set {
template <typename Set> constexpr auto is_countable(const Set &set) {
  if constexpr (std::same_as<Set, empty> || type_traits::is_tuple_v<Set> ||
                std::ranges::range<Set>) {
    return std::true_type{};
  } else {
    return std::false_type{};
  }
}
} // namespace math::set
