
#pragma once

#include <math/set/empty.hpp>
#include <math/set/set.hpp>
#include <tuple>

namespace math::set {
/**
 * @brief Non owning view that represents the concatination of the underlying
 *        sets.
 *
 * @tparam Sets Types of the sets represnented by this.
 */
template <typename... Sets>
requires(set<Sets> &&...) struct flattening_view {
  // Constructors.
  flattening_view() = delete;

  constexpr flattening_view(const flattening_view &) = default;
  constexpr flattening_view(flattening_view &&) = default;
  constexpr flattening_view &operator=(const flattening_view &) = default;
  constexpr flattening_view &operator=(flattening_view &&) = default;

  constexpr flattening_view(Sets &...sets) : sets{sets...} {
    static_assert(::math::set::set<flattening_view>,
                  "math::set::flattening_view must work as a set.");
  }

  // Methods.
  constexpr auto contains(empty) const noexcept -> bool { return true; }
  constexpr auto contains(const auto &value) const
      -> bool requires(!is_empty_set<decltype(value)>) {
    return std::apply(
        [&value](const auto &...sets) {
          return (::math::set::contains(sets, value) || ...);
        },
        sets);
  }

  // Members.
  std::tuple<Sets &...> sets;
};
} // namespace math::set