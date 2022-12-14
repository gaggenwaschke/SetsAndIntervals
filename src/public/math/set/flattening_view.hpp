
#pragma once

#include <math/set/element_of.hpp>
#include <math/set/empty.hpp>
#include <tuple>

namespace math {
namespace set {
/**
 * @brief Non owning view that represents the concatenation of the underlying
 *        sets.
 *
 * @tparam FlatteningOperation Operation used to flatten the contained sets.
 * @tparam Sets                Types of the sets represented by this.
 */
template <typename FlatteningOperation, typename... Sets>
  requires(set<Sets> && ...)
struct flattening_view {
  // Constructors.
  constexpr flattening_view(FlatteningOperation, const Sets &...sets) noexcept
      : sets{sets...} {
    static_assert(::math::set::set<flattening_view>,
                  "math::set::flattening_view must work as a set.");
  }

  // Members.
  std::tuple<const Sets &...> sets;
};

template <typename Value, typename FlatteningOperation, typename... Sets>
struct custom_is_element_of<Value,
                            flattening_view<FlatteningOperation, Sets...>> {
  constexpr auto
  operator()(const Value &value,
             const flattening_view<FlatteningOperation, Sets...> &view) {
    return std::apply(
        [&value](const auto &...sets) {
          return FlatteningOperation{}(
              ::math::set::is_element_of(value, sets)...);
        },
        view.sets);
  }
};
} // namespace set
} // namespace math