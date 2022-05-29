
#include <catch2/catch.hpp>
#include <math/set/operators.hpp>
#include <math/set/set.hpp>

TEST_CASE("math::set operator conjunction", "[]") {
  constexpr static std::array<int, 3> a1{1, 2, 3};
  constexpr static std::array<int, 2> a2{4, 5};

  math::set::empty empty{};

  CHECK((empty & empty) == empty);
  CHECK((empty | empty) == empty);

  CHECK((a1 & empty) == empty);
  CHECK((empty & a1) == empty);

  CHECK((a2 | empty) == a2);
  CHECK((empty | a2) == a2);

  //  constexpr static auto disjunction = a1 | a2;
  //  CHECK(std::same_as<decltype(disjunction), std::array<int, 5>>);
  //  CHECK(math::set::contains(disjunction, 1));
  //  CHECK(math::set::contains(disjunction, 2));
  //  CHECK(math::set::contains(disjunction, 3));
  //  CHECK(math::set::contains(disjunction, 4));
  //  CHECK(math::set::contains(disjunction, 5));
}