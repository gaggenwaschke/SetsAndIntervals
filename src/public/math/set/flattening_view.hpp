
#pragma once

#include <math/set/empty.hpp>
#include <math/set/set.hpp>
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

  // Methods.
  template <typename Value> constexpr bool contains(const Value &value) const {
    if constexpr (is_empty_set<Value>) {
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
  std::tuple<const Sets &...> sets;
};
} // namespace set
} // namespace math