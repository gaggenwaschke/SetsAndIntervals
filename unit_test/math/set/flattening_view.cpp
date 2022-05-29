
#include <catch2/catch.hpp>
#include <math/set/flattening_view.hpp>

TEST_CASE("math::set::flattening_view", "[]") {
  std::array<int, 2> a{1, 2};
  std::vector<int> b{3, 4};

  math::set::flattening_view view{a, b};

  CHECK(view.contains(math::set::empty{}));
  CHECK_FALSE(view.contains(0));
  CHECK(view.contains(1));
  CHECK(view.contains(2));
  CHECK(view.contains(3));
  CHECK(view.contains(4));
}

TEST_CASE("math::set::contains for math::set::flattening_view", "[]") {
  std::array<int, 2> a{1, 2};
  std::vector<int> b{3, 4};

  math::set::flattening_view view{a, b};

  CHECK(math::set::set<decltype(view)>);
  CHECK(math::set::contains(view, math::set::empty{}));
  CHECK_FALSE(math::set::contains(view, 0));
  CHECK(math::set::contains(view, 1));
  CHECK(math::set::contains(view, 2));
  CHECK(math::set::contains(view, 3));
  CHECK(math::set::contains(view, 4));
}