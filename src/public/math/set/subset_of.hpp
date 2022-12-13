#pragma once

#include "math/set/element_of.hpp"

namespace math {
namespace set {
template <typename Subset, typename Superset> struct custom_is_subset_of;

template <typename Subset, typename Superset>
  requires(set<Subset> && set<Superset>)
constexpr auto is_subset_of(const Subset &subset, const Superset &superset) {
  if constexpr (is_empty_set<Subset>) {
    return std::true_type{};
  } else if constexpr (is_empty_set<Superset>) {
    return std::false_type{};
  } else if constexpr (type_traits::is_complete_v<
                           custom_is_subset_of<Subset, Superset>>) {
    return custom_is_subset_of<Subset, Superset>{}(subset, superset);
  } else if constexpr (std::is_base_of_v<Subset, Superset>) {
    return std::true_type{};
  } else if constexpr (std::is_base_of_v<Superset, Subset>) {
    return std::false_type{};
  } else if constexpr (std::ranges::range<Subset> && !is_infinite<Subset>) {
    for (const auto &element : subset) {
      if (!is_element_of(element, superset)) {
        return false;
      }
    }
    return true;
  } else if constexpr (type_traits::is_tuple_v<Subset>) {
    return std::apply(
        [&superset](const auto &...elements) {
          return (is_element_of(elements, superset) && ...);
        },
        subset);
  } else {
    static_assert(std::same_as<std::false_type, std::pair<Subset, Superset>>,
                  "No implementation for is_subset_of found!");
  }
}

template <typename Subset, typename Superset>
constexpr auto is_superset_of(const Superset &superset, const Subset &subset) {
  return is_subset_of<Subset, Superset>(subset, superset);
}
} // namespace set
} // namespace math
