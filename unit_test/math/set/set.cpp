
#include <catch2/catch.hpp>
#include <math/set/set.hpp>

#include <array>
#include <vector>

namespace mock {
struct NonComparable {};

struct sub {};
struct super : sub {};
} // namespace mock

using math::set::get_cardinality;
using math::set::is_element_of;
using math::set::is_subset_of;
using math::set::set;

TEST_CASE("get_cardinality", "[]") {
  std::array<int, 5> array{};
  std::vector<int> vector{1, 2};
  std::tuple<int, char, int> tuple{};

  CHECK(get_cardinality(array) == 5);
  CHECK(get_cardinality(vector) == 2);
  CHECK(get_cardinality(tuple) == 3);
}

TEST_CASE("is_element_of for math::set::empty", "[]") {
  CHECK(is_element_of(math::set::empty{}, math::set::empty{}));
}

TEST_CASE("is_element_of for ranges", "[]") {
  std::array<int, 3> array{1, 2, 3};

  CHECK(set<decltype(array)>);
  CHECK(is_element_of(math::set::empty{}, array));
  CHECK(is_element_of(1, array));
  CHECK(is_element_of(2, array));
  CHECK(is_element_of(3, array));
  CHECK_FALSE(is_element_of(0, array));
  CHECK_FALSE(is_element_of(4, array));
  CHECK_FALSE(is_element_of(mock::NonComparable{}, array));

  std::vector<int> vector{4, 5, 6};
  CHECK(set<decltype(vector)>);
  CHECK(is_element_of(math::set::empty{}, vector));
  CHECK(is_element_of(4, vector));
  CHECK(is_element_of(5, vector));
  CHECK(is_element_of(6, vector));
  CHECK_FALSE(is_element_of(0, vector));
  CHECK_FALSE(is_element_of(7, vector));
  CHECK_FALSE(is_element_of(mock::NonComparable{}, vector));
}

TEST_CASE("is_element_of for tuples", "[]") {
  std::tuple tuple{1, 2, "Hello", 'W'};

  CHECK(set<decltype(tuple)>);
  CHECK(is_element_of(math::set::empty{}, tuple));
  CHECK_FALSE(is_element_of(0, tuple));
  CHECK(is_element_of(1, tuple));
  CHECK(is_element_of(2, tuple));
  CHECK_FALSE(is_element_of(3, tuple));
  CHECK(is_element_of("Hello", tuple));
  CHECK(is_element_of('W', tuple));
  CHECK_FALSE(is_element_of(mock::NonComparable{}, tuple));
}

TEST_CASE("is_subset_of", "[]") {
  std::tuple subset{1, "hello"};
  std::tuple superset{"hello", 2, 4, 1};
  std::array<int, 3> not_a_subset{1, 2, 3};

  CHECK(is_subset_of(math::set::empty{}, math::set::empty{}));
  CHECK(is_subset_of(math::set::empty{}, subset));
  CHECK(is_subset_of(math::set::empty{}, superset));
  CHECK(is_subset_of(math::set::empty{}, not_a_subset));
  CHECK(is_subset_of(subset, superset));
  CHECK(is_subset_of(mock::sub{}, mock::super{}));
  CHECK_FALSE(is_subset_of(not_a_subset, superset));
  CHECK_FALSE(is_subset_of(superset, subset));
  CHECK_FALSE(is_subset_of(mock::super{}, mock::sub{}));
}