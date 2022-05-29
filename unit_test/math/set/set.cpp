
#include <catch2/catch.hpp>
#include <math/set/set.hpp>

#include <array>
#include <vector>

namespace mock {
struct NonComparable {};
} // namespace mock

TEST_CASE("math::set::contains for math::set::empty", "[]") {
  CHECK(math::set::contains(math::set::empty{}, math::set::empty{}));
}

TEST_CASE("math::set::contains for ranges", "[]") {
  std::array<int, 3> array{1, 2, 3};

  CHECK(math::set::set<decltype(array)>);
  CHECK(math::set::contains(array, math::set::empty{}));
  CHECK(math::set::contains(array, 1));
  CHECK(math::set::contains(array, 2));
  CHECK(math::set::contains(array, 3));
  CHECK_FALSE(math::set::contains(array, 0));
  CHECK_FALSE(math::set::contains(array, 4));
  CHECK_FALSE(math::set::contains(array, mock::NonComparable{}));

  std::vector<int> vector{4, 5, 6};
  CHECK(math::set::set<decltype(vector)>);
  CHECK(math::set::contains(vector, math::set::empty{}));
  CHECK(math::set::contains(vector, 4));
  CHECK(math::set::contains(vector, 5));
  CHECK(math::set::contains(vector, 6));
  CHECK_FALSE(math::set::contains(vector, 0));
  CHECK_FALSE(math::set::contains(vector, 7));
  CHECK_FALSE(math::set::contains(vector, mock::NonComparable{}));
}

TEST_CASE("math::set::contains for tuples", "[]") {
  std::tuple tuple{1, 2, "Hello", 'W'};

  CHECK(math::set::set<decltype(tuple)>);
  CHECK(math::set::contains(tuple, math::set::empty{}));
  CHECK_FALSE(math::set::contains(tuple, 0));
  CHECK(math::set::contains(tuple, 1));
  CHECK(math::set::contains(tuple, 2));
  CHECK_FALSE(math::set::contains(tuple, 3));
  CHECK(math::set::contains(tuple, "Hello"));
  CHECK(math::set::contains(tuple, 'W'));
  CHECK_FALSE(math::set::contains(tuple, mock::NonComparable{}));
}
