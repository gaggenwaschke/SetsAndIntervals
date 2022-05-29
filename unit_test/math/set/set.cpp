
#include <catch2/catch.hpp>
#include <math/set/set.hpp>

#include <array>
#include <vector>

namespace mock {
struct NonComparable {};
} // namespace mock

TEST_CASE("math::set::contains for math::set::empty", "[]") {
  CHECK(math::set::element_of(math::set::empty{}, math::set::empty{}));
}

TEST_CASE("math::set::contains for ranges", "[]") {
  std::array<int, 3> array{1, 2, 3};

  CHECK(math::set::set<decltype(array)>);
  CHECK(math::set::element_of(math::set::empty{}, array));
  CHECK(math::set::element_of(1, array));
  CHECK(math::set::element_of(2, array));
  CHECK(math::set::element_of(3, array));
  CHECK_FALSE(math::set::element_of(0, array));
  CHECK_FALSE(math::set::element_of(4, array));
  CHECK_FALSE(math::set::element_of(mock::NonComparable{}, array));

  std::vector<int> vector{4, 5, 6};
  CHECK(math::set::set<decltype(vector)>);
  CHECK(math::set::element_of(math::set::empty{}, vector));
  CHECK(math::set::element_of(4, vector));
  CHECK(math::set::element_of(5, vector));
  CHECK(math::set::element_of(6, vector));
  CHECK_FALSE(math::set::element_of(0, vector));
  CHECK_FALSE(math::set::element_of(7, vector));
  CHECK_FALSE(math::set::element_of(mock::NonComparable{}, vector));
}

TEST_CASE("math::set::contains for tuples", "[]") {
  std::tuple tuple{1, 2, "Hello", 'W'};

  CHECK(math::set::set<decltype(tuple)>);
  CHECK(math::set::element_of(math::set::empty{}, tuple));
  CHECK_FALSE(math::set::element_of(0, tuple));
  CHECK(math::set::element_of(1, tuple));
  CHECK(math::set::element_of(2, tuple));
  CHECK_FALSE(math::set::element_of(3, tuple));
  CHECK(math::set::element_of("Hello", tuple));
  CHECK(math::set::element_of('W', tuple));
  CHECK_FALSE(math::set::element_of(mock::NonComparable{}, tuple));
}
