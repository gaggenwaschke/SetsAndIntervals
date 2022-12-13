#pragma once

#include "math/infinity.hpp"
#include "math/set/empty.hpp"
#include "math/type_traits.hpp"
#include <ranges>
#include <type_traits>

namespace math {
namespace set {
template <typename Set> struct custom_cardinality;

template <typename Set> constexpr auto get_cardinality(const Set &set) {
  if constexpr (is_empty_set<Set>) {
    return 0;
  } else if constexpr (type_traits::is_complete_v<custom_cardinality<Set>>) {
    return custom_cardinality<Set>{}(set);
  } else if constexpr (type_traits::is_tuple_v<Set>) {
    return std::tuple_size_v<Set>;
  } else if constexpr (std::is_same_v<infinity_type,
                                      std::ranges::sentinel_t<Set>>) {
    return infinity;
  } else if constexpr (std::ranges::sized_range<Set>) {
    return std::ranges::size(set);
  } else {
    static_assert(std::is_same_v<Set, Set &>,
                  "No implementation for get_cardinality() found!");
  }
}

template <typename Set>
concept is_infinite = std::is_same_v<
    infinity_type,
    std::invoke_result_t<decltype(get_cardinality<Set>), const Set &>>;
} // namespace set
} // namespace math
