
#pragma once

#include <math/set/empty.hpp>
#include <math/set/set.hpp>
#include <tuple>

namespace math::set {
struct conjunction {
  constexpr auto operator()(const auto &...args) -> bool {
    return (args && ...);
  };
};
struct disjunction {
  constexpr auto operator()(const auto &...args) -> bool {
    return (args || ...);
  };
};
struct symmetric_difference {
  constexpr auto operator()(const auto &...args) -> bool {
    return (args ^ ...);
  }
};

/**
 * @brief Non owning view that represents the concatination of the underlying
 *        sets.
 *
 * @tparam FlatteningOperation Operation used to flatten the contained sets.
 * @tparam Sets                Types of the sets represnented by this.
 */
template <typename FlatteningOperation, typename... Sets>
requires(set<Sets> &&...) struct flattening_view {
  // Constructors.
  flattening_view() = delete;

  constexpr flattening_view(const flattening_view &) = default;
  constexpr flattening_view(flattening_view &&) = default;
  constexpr flattening_view &operator=(const flattening_view &) = default;
  constexpr flattening_view &operator=(flattening_view &&) = default;

  constexpr flattening_view(FlatteningOperation, Sets &...sets) noexcept
      : sets{sets...} {
    static_assert(::math::set::set<flattening_view>,
                  "math::set::flattening_view must work as a set.");
  }

  // Methods.
  constexpr auto contains(const auto &value) const -> bool {
    if constexpr (is_empty_set<decltype(value)>) {
      return true;
    } else {
      return std::apply(
          [&value](const auto &...sets) {
            return FlatteningOperation{}(
                ::math::set::is_element_of(value, sets)...);
          },
          sets);
    }
  }

  // Members.
  std::tuple<Sets &...> sets;
};
} // namespace math::set