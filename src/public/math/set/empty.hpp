
#pragma once

namespace math {
namespace set {
/**
 * @brief Empty set.
 *
 * @details Is contained in any set and in itself.
 */
struct empty {};

template <typename Set>
concept is_empty_set = std::same_as<std::remove_cvref_t<Set>, set::empty>;

constexpr std::true_type operator==(empty, empty) { return {}; }
} // namespace set
} // namespace math
