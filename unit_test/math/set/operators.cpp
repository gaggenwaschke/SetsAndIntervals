
#include <catch2/catch.hpp>
#include <math/set/operators.hpp>
#include <math/set/set.hpp>

namespace mock {
struct NonComparable {};
} // namespace mock

TEST_CASE("math::set operator conjunction", "[]") {
  constexpr static std::array<int, 3> a1{1, 2, 3};
  constexpr static std::array<int, 4> a2{1, 2, 4, 5};

  math::set::empty empty{};

  CHECK((empty & empty) == empty);
  CHECK((a1 & empty) == empty);
  CHECK((empty & a1) == empty);

  constexpr static auto conjunction = a1 & a2;

  CHECK(math::set::set<decltype(conjunction)>);
  CHECK_FALSE(math::set::is_element_of(0, conjunction));
  CHECK(math::set::is_element_of(1, conjunction));
  CHECK(math::set::is_element_of(2, conjunction));
  CHECK_FALSE(math::set::is_element_of(3, conjunction));
  CHECK_FALSE(math::set::is_element_of(4, conjunction));
  CHECK_FALSE(math::set::is_element_of(5, conjunction));
  CHECK_FALSE(math::set::is_element_of(mock::NonComparable{}, conjunction));
}

TEST_CASE("math::set operator disjunction", "[]") {
  constexpr static std::array<int, 3> a1{1, 2, 3};
  constexpr static std::array<int, 2> a2{4, 5};

  math::set::empty empty{};

  CHECK((empty | empty) == empty);
  CHECK((a2 | empty) == a2);
  CHECK((empty | a2) == a2);

  constexpr static auto disjunction = a1 | a2;

  CHECK(math::set::set<decltype(disjunction)>);
  CHECK_FALSE(math::set::is_element_of(0, disjunction));
  CHECK(math::set::is_element_of(1, disjunction));
  CHECK(math::set::is_element_of(2, disjunction));
  CHECK(math::set::is_element_of(3, disjunction));
  CHECK(math::set::is_element_of(4, disjunction));
  CHECK(math::set::is_element_of(5, disjunction));
  CHECK_FALSE(math::set::is_element_of(mock::NonComparable{}, disjunction));
}

TEST_CASE("math::set operator symmetric difference", "[]") {
  constexpr static std::array<int, 3> a1{1, 2, 3};
  constexpr static std::array<int, 2> a2{3, 4};

  math::set::empty empty{};

  CHECK((empty ^ empty) == empty);
  CHECK((a1 ^ empty) == a1);
  CHECK((empty ^ a1) == a1);

  constexpr static auto symm_difference = a1 ^ a2;

  CHECK(math::set::set<decltype(symm_difference)>);
  CHECK_FALSE(math::set::is_element_of(0, symm_difference));
  CHECK(math::set::is_element_of(1, symm_difference));
  CHECK(math::set::is_element_of(2, symm_difference));
  CHECK_FALSE(math::set::is_element_of(3, symm_difference));
  CHECK(math::set::is_element_of(4, symm_difference));
  CHECK_FALSE(math::set::is_element_of(5, symm_difference));
  CHECK_FALSE(math::set::is_element_of(mock::NonComparable{}, symm_difference));
}
