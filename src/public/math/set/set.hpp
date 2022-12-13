
#pragma once

#include <array>
#include <concepts>
#include <math/set/empty.hpp>
#include <ranges>
#include <tuple>

namespace math {
namespace set {
namespace {
template <typename> struct is_tuple : std::false_type {};

template <typename... TupleElements>
struct is_tuple<std::tuple<TupleElements...>> : std::true_type {};

constexpr auto tuple_element_equals_any(const auto &element,
                                        const auto &value) noexcept -> bool {
  if constexpr (std::equality_comparable_with<decltype(element),
                                              decltype(value)>) {
    return element == value;
  } else {
    return false;
  }
}
} // namespace

template <typename Set>
concept set_members = requires(const Set &set) {
                        { set.contains(empty{}) } -> std::same_as<bool>;
                        { set.template contains<int>(1) } -> std::same_as<bool>;
                      };

/**
 * @brief Is-in or element operation.
 *
 * @param any_set
 * @param value
 * @return true
 * @return false
 */
constexpr auto is_element_of(const auto &value, const auto &any_set) noexcept
    -> bool {
  using value_type = std::remove_cvref_t<decltype(value)>;
  using set_type = std::remove_cvref_t<decltype(any_set)>;

  if constexpr (is_empty_set<value_type>) {
    return true;
  } else if constexpr (std::ranges::range<set_type>) {
    if constexpr (std::equality_comparable_with<
                      value_type, std::ranges::range_value_t<set_type>>) {
      return std::ranges::find(any_set, value) != std::cend(any_set);
    } else {
      return false;
    }
  } else if constexpr (is_tuple<set_type>::value) {
    return std::apply(
        [&value](const auto &...element) {
          return (tuple_element_equals_any(element, value) || ...);
        },
        any_set);
  } else {
    static_assert(set_members<set_type>,
                  "Set does not define math::set::set member functions!");
    return any_set.template contains<value_type>(value);
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

template <typename Subset, typename Superset>
  requires(set<Subset> && set<Superset>)
constexpr bool is_subset_of(const Subset &subset, const Superset &superset) {
  if constexpr (is_empty_set<Subset>) {
    return true;
  } else if constexpr (is_empty_set<Superset>) {
    return false;
  } else if constexpr (std::is_base_of_v<Subset, Superset>) {
    return true;
  } else if constexpr (std::ranges::range<Subset>) {
    for (const auto &element : subset) {
      if (!is_element_of(element, superset)) {
        return false;
      }
    }
    return true;
  } else if constexpr (is_tuple<Subset>::value) {
    return std::apply(
        [&superset](const auto &...elements) {
          return (is_element_of(elements, superset) && ...);
        },
        subset);
  } else {
    static_assert(set_members<Subset>,
                  "Set does not define math::set::set member functions!");
    return false;
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