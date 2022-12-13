
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

template <typename Set>
concept set_members = requires(const Set &set) {
                        { set.contains(empty{}) } -> std::same_as<bool>;
                        { set.template contains<int>(1) } -> std::same_as<bool>;
                      };

template <typename Candidate>
concept is_infinite_range =
    std::ranges::range<Candidate> &&
    std::same_as<std::ranges::sentinel_t<Candidate>, infinity>;

/**
 * @brief Is-in or element operation.
 *
 * @param any_set
 * @param value
 * @return true
 * @return false
 */
template <typename Value, typename Set>
constexpr auto is_element_of(const Value &value, const Set &any_set) noexcept
    -> bool {
  if constexpr (is_empty_set<Value>) {
    return true;
  } else if constexpr (std::ranges::range<Set>) {
    if constexpr (std::equality_comparable_with<
                      Value, std::ranges::range_value_t<Set>>) {
      return std::ranges::find(any_set, value) != std::cend(any_set);
    } else {
      return false;
    }
  } else if constexpr (type_traits::is_tuple<Set>::value) {
    return std::apply(
        [&value](const auto &...element) {
          return (details::tuple_element_equals_any(element, value) || ...);
        },
        any_set);
  } else {
    static_assert(set_members<Set>,
                  "Set does not define math::set::set member functions!");
    return any_set.template contains<Value>(value);
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
concept has_custom_subset_check = false;

template <typename Subset, typename Superset>
  requires(set<Subset> && set<Superset>)
constexpr bool is_subset_of(const Subset &subset, const Superset &superset) {
  if constexpr (is_empty_set<Subset>) {
    return true;
  } else if constexpr (is_empty_set<Superset>) {
    return false;
  } else if constexpr (type_traits::is_complete<
                           custom_subset_check<Subset, Superset>>::value) {
    return custom_subset_check<Subset, Superset>{}(subset, superset);
  } else if constexpr (std::is_base_of_v<Subset, Superset>) {
    return true;
  } else if constexpr (std::ranges::range<Subset> &&
                       !is_infinite_range<Subset>) {
    for (const auto &element : subset) {
      if (!is_element_of(element, superset)) {
        return false;
      }
    }
    return true;
  } else if constexpr (type_traits::is_tuple<Subset>::value) {
    return std::apply(
        [&superset](const auto &...elements) {
          return (is_element_of(elements, superset) && ...);
        },
        subset);
  } else {
    return false; // static_assert(false, "No implementation for is_subset_of
                  // found!");
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
