#pragma once

#include "math/set/empty.hpp"
#include "math/type_traits.hpp"
#include <ranges>
#include <type_traits>

namespace math {
namespace set {
namespace details {
constexpr auto tuple_element_equals_any(const auto &element,
                                        const auto &value) noexcept {
  if constexpr (std::equality_comparable_with<decltype(element),
                                              decltype(value)>) {
    return element == value;
  } else {
    return std::false_type{};
  }
}
} // namespace details

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
constexpr auto is_element_of(const Value &value, const Set &set) noexcept {
  if constexpr (is_empty_set<Value>) {
    return std::true_type{};
  } else if constexpr (is_empty_set<Set>) {
    return std::false_type{};
  } else if constexpr (type_traits::is_complete_v<
                           custom_is_element_of<Value, Set>>) {
    return custom_is_element_of<Value, Set>{}(value, set);
  } else if constexpr (std::ranges::range<Set>) {
    if constexpr (std::equality_comparable_with<
                      Value, std::ranges::range_value_t<Set>>) {
      return std::ranges::find(set, value) != std::cend(set);
    } else {
      return std::false_type{};
    }
  } else if constexpr (type_traits::is_tuple_v<Set>) {
    return std::apply(
        [&value](const auto &...element) {
          return (details::tuple_element_equals_any(element, value) || ...);
        },
        set);
  } else {
    // Fall through to false.
    return std::false_type{};
  }
}

template <typename Candidate>
concept set = is_empty_set<Candidate> ||
              requires(const Candidate &candidate) {
                {
                  ::math::set::is_element_of(empty{}, candidate)
                  } -> std::convertible_to<bool>;
                {
                  ::math::set::is_element_of(int{1}, candidate)
                  } -> std::convertible_to<bool>;
              };
} // namespace set
} // namespace math
