
#include <catch2/catch.hpp>
#include <math/interval.hpp>
#include <math/set/set.hpp>

#include <array>
#include <vector>

namespace mock {
struct NonComparable {};
} // namespace mock

TEST_CASE("math::set::is_element_of for math::set::empty", "[]") {
  CHECK(math::set::is_element_of(math::set::empty{}, math::set::empty{}));
}

TEST_CASE("math::set::is_element_of for ranges", "[]") {
  std::array<int, 3> array{1, 2, 3};

  CHECK(math::set::set<decltype(array)>);
  CHECK(math::set::is_element_of(math::set::empty{}, array));
  CHECK(math::set::is_element_of(1, array));
  CHECK(math::set::is_element_of(2, array));
  CHECK(math::set::is_element_of(3, array));
  CHECK_FALSE(math::set::is_element_of(0, array));
  CHECK_FALSE(math::set::is_element_of(4, array));
  CHECK_FALSE(math::set::is_element_of(mock::NonComparable{}, array));

  std::vector<int> vector{4, 5, 6};
  CHECK(math::set::set<decltype(vector)>);
  CHECK(math::set::is_element_of(math::set::empty{}, vector));
  CHECK(math::set::is_element_of(4, vector));
  CHECK(math::set::is_element_of(5, vector));
  CHECK(math::set::is_element_of(6, vector));
  CHECK_FALSE(math::set::is_element_of(0, vector));
  CHECK_FALSE(math::set::is_element_of(7, vector));
  CHECK_FALSE(math::set::is_element_of(mock::NonComparable{}, vector));
}

TEST_CASE("math::set::is_element_of for tuples", "[]") {
  std::tuple tuple{1, 2, "Hello", 'W'};

  CHECK(math::set::set<decltype(tuple)>);
  CHECK(math::set::is_element_of(math::set::empty{}, tuple));
  CHECK_FALSE(math::set::is_element_of(0, tuple));
  CHECK(math::set::is_element_of(1, tuple));
  CHECK(math::set::is_element_of(2, tuple));
  CHECK_FALSE(math::set::is_element_of(3, tuple));
  CHECK(math::set::is_element_of("Hello", tuple));
  CHECK(math::set::is_element_of('W', tuple));
  CHECK_FALSE(math::set::is_element_of(mock::NonComparable{}, tuple));
}

TEST_CASE("math::set::is_subset_of", "[]") {
  std::tuple subset{1, "hello"};
  std::tuple superset{"hello", 2, 4, 1};
  std::array<int, 3> not_a_subset{1, 2, 3};
  math::interval interval{1, 2};

  CHECK(math::set::is_subset_of(math::set::empty{}, math::set::empty{}));
  CHECK(math::set::is_subset_of(math::set::empty{}, subset));
  CHECK(math::set::is_subset_of(math::set::empty{}, superset));
  CHECK(math::set::is_subset_of(math::set::empty{}, not_a_subset));
  CHECK(math::set::is_subset_of(math::set::empty{}, interval));
  CHECK(math::set::is_subset_of(subset, superset));
  CHECK(math::set::is_subset_of(interval, superset));
  CHECK_FALSE(math::set::is_subset_of(not_a_subset, superset));
  CHECK_FALSE(math::set::is_subset_of(superset, subset));
}