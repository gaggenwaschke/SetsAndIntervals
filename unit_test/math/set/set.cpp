
#include <catch2/catch.hpp>
#include <math/set/set.hpp>

#include <array>
#include <vector>

namespace mock {
struct Empty {};
} // namespace mock

TEST_CASE("math::set::contains for ranges", "[]") {
  std::array<int, 3> array{1, 2, 3};

  CHECK(math::set::contains(array, 1));
  CHECK(math::set::contains(array, 2));
  CHECK(math::set::contains(array, 3));
  CHECK_FALSE(math::set::contains(array, 0));
  CHECK_FALSE(math::set::contains(array, 4));
  CHECK_FALSE(math::set::contains(array, mock::Empty{}));

  std::vector<int> vector{4, 5, 6};
  CHECK(math::set::contains(vector, 4));
  CHECK(math::set::contains(vector, 5));
  CHECK(math::set::contains(vector, 6));
  CHECK_FALSE(math::set::contains(vector, 0));
  CHECK_FALSE(math::set::contains(vector, 7));
  CHECK_FALSE(math::set::contains(vector, mock::Empty{}));
}

TEST_CASE("math::set::contains for tuples", "[]") {
  std::tuple tuple{1, 2, "Hello", 'W'};
  CHECK_FALSE(math::set::contains(tuple, 0));
  CHECK(math::set::contains(tuple, 1));
  CHECK(math::set::contains(tuple, 2));
  CHECK_FALSE(math::set::contains(tuple, 3));
  CHECK(math::set::contains(tuple, "Hello"));
  CHECK(math::set::contains(tuple, 'W'));
  CHECK_FALSE(math::set::contains(tuple, mock::Empty{}));
}

TEST_CASE("math::set::contains for intervals", "[]") {
  math::interval interval_int{1, 3};
  CHECK_FALSE(math::set::contains(interval_int, 0));
  CHECK(math::set::contains(interval_int, 1));
  CHECK(math::set::contains(interval_int, 2));
  CHECK_FALSE(math::set::contains(interval_int, 3));
  CHECK_FALSE(math::set::contains(interval_int, mock::Empty{}));
}