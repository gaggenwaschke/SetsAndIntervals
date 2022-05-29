
#include <catch2/catch.hpp>
#include <math/interval.hpp>
#include <math/set/set.hpp>

namespace mock {
struct NonComparable {};
} // namespace mock

TEST_CASE("math::interval<int>", "[]") {
  {
    math::interval<int> interval{1, 3};

    CHECK(interval.contains(math::set::empty{}));
    CHECK_FALSE(interval.contains(0));
    CHECK(interval.contains(1));
    CHECK(interval.contains(2));
    CHECK_FALSE(interval.contains(3));
  }
}

TEST_CASE("math::set::contains for intervals", "[]") {
  math::interval interval{1, 3};

  CHECK(math::set::set<decltype(interval)>);
  CHECK(math::set::contains(interval, math::set::empty{}));
  CHECK_FALSE(math::set::contains(interval, 0));
  CHECK(math::set::contains(interval, 1));
  CHECK(math::set::contains(interval, 2));
  CHECK_FALSE(math::set::contains(interval, 3));
  CHECK_FALSE(math::set::contains(interval, mock::NonComparable{}));
}