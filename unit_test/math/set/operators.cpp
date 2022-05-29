
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
  CHECK_FALSE(math::set::contains(conjunction, 0));
  CHECK(math::set::contains(conjunction, 1));
  CHECK(math::set::contains(conjunction, 2));
  CHECK_FALSE(math::set::contains(conjunction, 3));
  CHECK_FALSE(math::set::contains(conjunction, 4));
  CHECK_FALSE(math::set::contains(conjunction, 5));
  CHECK_FALSE(math::set::contains(conjunction, mock::NonComparable{}));
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
  CHECK_FALSE(math::set::contains(disjunction, 0));
  CHECK(math::set::contains(disjunction, 1));
  CHECK(math::set::contains(disjunction, 2));
  CHECK(math::set::contains(disjunction, 3));
  CHECK(math::set::contains(disjunction, 4));
  CHECK(math::set::contains(disjunction, 5));
  CHECK_FALSE(math::set::contains(disjunction, mock::NonComparable{}));
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
  CHECK_FALSE(math::set::contains(symm_difference, 0));
  CHECK(math::set::contains(symm_difference, 1));
  CHECK(math::set::contains(symm_difference, 2));
  CHECK_FALSE(math::set::contains(symm_difference, 3));
  CHECK(math::set::contains(symm_difference, 4));
  CHECK_FALSE(math::set::contains(symm_difference, 5));
  CHECK_FALSE(math::set::contains(symm_difference, mock::NonComparable{}));
}
