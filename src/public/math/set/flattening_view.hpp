
#pragma once

#include <functional>
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
  constexpr flattening_view(FlatteningOperation flattening_operation,
                            const Sets &...sets) noexcept
      : flattening_operation{flattening_operation}, sets{sets...} {}

  // Members.
  FlatteningOperation flattening_operation;
  std::tuple<const Sets &...> sets;
};

template <typename Value, typename FlatteningOperation, typename... Sets>
struct custom_is_element_of<Value,
                            flattening_view<FlatteningOperation, Sets...>> {
  constexpr auto
  operator()(const Value &value,
             const flattening_view<FlatteningOperation, Sets...> &view) {
    const auto &operation = view.flattening_operation;
    return std::apply(
        [&value, operation](const Sets &...sets) {
          return std::invoke(operation,
                             is_element_of<Value, Sets>(value, sets)...);
        },
        view.sets);
  }
};
} // namespace set
} // namespace math