
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <math/set.hpp>

using math::set::empty;
using math::set::is_element_of;
using math::set::set;

namespace mock {
struct NonComparable {};
} // namespace mock

TEST_CASE("math::set operator conjunction", "[math::set][operators]") {
  constexpr static std::array<int, 3> a1{1, 2, 3};
  constexpr static std::array<int, 4> a2{1, 2, 4, 5};

  empty empty{};

  CHECK((empty & empty) == empty);
  CHECK((a1 & empty) == empty);
  CHECK((empty & a1) == empty);

  constexpr static auto conjunction = a1 & a2;

  CHECK(set<decltype(conjunction)>);
  CHECK_FALSE(is_element_of(0, conjunction));
  CHECK(is_element_of(1, conjunction));
  CHECK(is_element_of(2, conjunction));
  CHECK_FALSE(is_element_of(3, conjunction));
  CHECK_FALSE(is_element_of(4, conjunction));
  CHECK_FALSE(is_element_of(5, conjunction));
  CHECK_FALSE(is_element_of(mock::NonComparable{}, conjunction));
}

TEST_CASE("math::set operator disjunction", "[math::set][operators]") {
  constexpr static std::array<int, 3> a1{1, 2, 3};
  constexpr static std::array<int, 2> a2{4, 5};

  empty empty{};

  CHECK((empty | empty) == empty);
  CHECK((a2 | empty) == a2);
  CHECK((empty | a2) == a2);

  constexpr static auto disjunction = a1 | a2;

  CHECK(set<decltype(disjunction)>);
  CHECK_FALSE(is_element_of(0, disjunction));
  CHECK(is_element_of(1, disjunction));
  CHECK(is_element_of(2, disjunction));
  CHECK(is_element_of(3, disjunction));
  CHECK(is_element_of(4, disjunction));
  CHECK(is_element_of(5, disjunction));
  CHECK_FALSE(is_element_of(mock::NonComparable{}, disjunction));
}

TEST_CASE("math::set operator symmetric difference", "[math::set][operators]") {
  constexpr static std::array<int, 3> a1{1, 2, 3};
  constexpr static std::array<int, 2> a2{3, 4};

  empty empty{};

  CHECK((empty ^ empty) == empty);
  CHECK((a1 ^ empty) == a1);
  CHECK((empty ^ a1) == a1);

  constexpr static auto symm_difference = a1 ^ a2;

  CHECK(set<decltype(symm_difference)>);
  CHECK_FALSE(is_element_of(0, symm_difference));
  CHECK(is_element_of(1, symm_difference));
  CHECK(is_element_of(2, symm_difference));
  CHECK_FALSE(is_element_of(3, symm_difference));
  CHECK(is_element_of(4, symm_difference));
  CHECK_FALSE(is_element_of(5, symm_difference));
  CHECK_FALSE(is_element_of(mock::NonComparable{}, symm_difference));
}

TEST_CASE("operators for std::true_type and std::false_type", "[logic]") {
  CHECK(std::is_same_v<std::true_type,
                       decltype(std::true_type{} || std::true_type{})>);
  CHECK(std::is_same_v<std::true_type,
                       decltype(std::false_type{} || std::true_type{})>);
  CHECK(std::is_same_v<std::true_type,
                       decltype(std::true_type{} || std::false_type{})>);
  CHECK(std::is_same_v<std::false_type,
                       decltype(std::false_type{} || std::false_type{})>);
  CHECK(std::is_same_v<std::true_type, decltype(std::true_type{} || true)>);
  CHECK(std::is_same_v<std::true_type, decltype(std::true_type{} || false)>);
  CHECK(std::is_same_v<std::true_type, decltype(true || std::true_type{})>);
  CHECK(std::is_same_v<std::true_type, decltype(false || std::true_type{})>);

  CHECK(std::is_same_v<std::true_type,
                       decltype(std::true_type{} && std::true_type{})>);
  CHECK(std::is_same_v<std::false_type,
                       decltype(std::false_type{} && std::true_type{})>);
  CHECK(std::is_same_v<std::false_type,
                       decltype(std::true_type{} && std::false_type{})>);
  CHECK(std::is_same_v<std::false_type,
                       decltype(std::false_type{} && std::false_type{})>);
  CHECK(std::is_same_v<std::false_type, decltype(std::false_type{} && true)>);
  CHECK(std::is_same_v<std::false_type, decltype(std::false_type{} && false)>);
  CHECK(std::is_same_v<std::false_type, decltype(true && std::false_type{})>);
  CHECK(std::is_same_v<std::false_type, decltype(false && std::false_type{})>);

  CHECK(std::is_same_v<std::false_type,
                       decltype(std::true_type{} ^ std::true_type{})>);
  CHECK(std::is_same_v<std::true_type,
                       decltype(std::false_type{} ^ std::true_type{})>);
  CHECK(std::is_same_v<std::true_type,
                       decltype(std::true_type{} ^ std::false_type{})>);
  CHECK(std::is_same_v<std::false_type,
                       decltype(std::false_type{} ^ std::false_type{})>);
}
