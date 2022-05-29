
#pragma once

namespace math {
template <typename Number> struct constant {
  // Constructors.
  constant() = delete;
  constant(const constant &) = delete;
  constant(constant &&) = delete;
  constant &operator=(const operator&) = delete;
  constant &operator=(operator&&) = delete;

  constexpr constant(Number constant) noexcept;

  // Members.
  const Number value;
};
} // namespace math

// ---
// Implementation
// ---

namespace math {
template <typename Number>
constexpr constant<Number>::constant(Number constant) noexcept
    : value{constant} {}
} // namespace math