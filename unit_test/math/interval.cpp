
#include <catch2/catch.hpp>
#include <math/interval.hpp>

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