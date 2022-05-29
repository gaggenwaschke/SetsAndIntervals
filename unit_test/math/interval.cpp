
#include <catch2/catch.hpp>
#include <math/interval.hpp>

TEST_CASE("math::interval<int>", "[]") {
  {
    math::interval<int> interval_int{1, 3};
    CHECK_FALSE(interval_int.contains(0));
    CHECK(interval_int.contains(1));
    CHECK(interval_int.contains(2));
    CHECK_FALSE(interval_int.contains(3));
  }
}