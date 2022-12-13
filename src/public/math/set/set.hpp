
#pragma once

#include "math/infinity.hpp"
#include "math/set/empty.hpp"
#include "math/type_traits.hpp"
#include <array>
#include <concepts>
#include <ranges>
#include <tuple>
#include <vector>

namespace math {
namespace set {
namespace details {
constexpr auto tuple_element_equals_any(const auto &element,
                                        const auto &value) noexcept -> bool {
  if constexpr (std::equality_comparable_with<decltype(element),
                                              decltype(value)>) {
    return element == value;
  } else {
    return false;
  }
}
} // namespace details

template <typename Candidate>
concept is_infinite_range =
    std::ranges::range<Candidate> &&
    std::same_as<std::ranges::sentinel_t<Candidate>, infinity>;

template <typename Value, typename Set> struct custom_is_element_of;

/**
 * @brief Is-in or element operation.
 *
 * @param set
 * @param value
 * @return true
 * @return false
 */
template <typename Value, typename Set>
constexpr bool is_element_of(const Value &value, const Set &set) noexcept {
  if constexpr (is_empty_set<Value>) {
    return true;
  } else if constexpr (is_empty_set<Set>) {
    return false;
  } else if constexpr (type_traits::is_complete_v<
                           custom_is_element_of<Value, Set>>) {
    return custom_is_element_of<Value, Set>{}(value, set);
  } else if constexpr (std::ranges::range<Set>) {
    if constexpr (std::equality_comparable_with<
                      Value, std::ranges::range_value_t<Set>>) {
      return std::ranges::find(set, value) != std::cend(set);
    } else {
      return false;
    }
  } else if constexpr (type_traits::is_tuple_v<Set>) {
    return std::apply(
        [&value](const auto &...element) {
          return (details::tuple_element_equals_any(element, value) || ...);
        },
        set);
  } else {
    // Fall through to false.
    return false;
  }
}

template <typename Candidate>
concept set = is_empty_set<Candidate> ||
              requires(const Candidate &candidate) {
                {
                  ::math::set::is_element_of(empty{}, candidate)
                  } -> std::same_as<bool>;
                {
                  ::math::set::is_element_of(int{1}, candidate)
                  } -> std::same_as<bool>;
              };

template <typename Subset, typename Superset> struct custom_subset_check;

template <typename Subset, typename Superset>
  requires(set<Subset> && set<Superset>)
constexpr bool is_subset_of(const Subset &subset, const Superset &superset) {
  if constexpr (is_empty_set<Subset>) {
    return true;
  } else if constexpr (is_empty_set<Superset>) {
    return false;
  } else if constexpr (type_traits::is_complete_v<
                           custom_subset_check<Subset, Superset>>) {
    return custom_subset_check<Subset, Superset>{}(subset, superset);
  } else if constexpr (std::is_base_of_v<Subset, Superset>) {
    return true;
  } else if constexpr (std::is_base_of_v<Superset, Subset>) {
    return false;
  } else if constexpr (std::ranges::range<Subset> &&
                       !is_infinite_range<Subset>) {
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
    static_assert(std::is_same_v<Subset, Subset &> &&
                      std::is_same_v<Superset, Superset &>,
                  "No implementation for is_subset_of found!");
  }
}

template <typename Subset, typename Superset>
constexpr bool is_superset_of(const Superset &superset, const Subset &subset) {
  return is_subset_of<Subset, Superset>(subset, superset);
}

// Static assertions.
static_assert(set<std::array<int, 3>>, "Array must work as a set.");
static_assert(set<std::vector<int>>, "Vector must work as a set.");
static_assert(set<std::tuple<int, char>>, "Tuple must work as a set.");
static_assert(set<empty>, "math::set::empty must work as set.");
} // namespace set
} // namespace math
