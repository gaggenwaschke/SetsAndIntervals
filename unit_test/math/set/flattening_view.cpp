
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <math/operations.hpp>
#include <math/set/flattening_view.hpp>
#include <vector>

using math::operations::disjunction;
using math::set::empty;
using math::set::flattening_view;
using math::set::is_element_of;
using math::set::set;

TEST_CASE("flattening_view", "[flattening_view][math::set]") {
  std::array<int, 2> a{1, 2};
  std::vector<int> b{3, 4};

  flattening_view view{disjunction, a, b};
  static_assert(::math::set::set<decltype(view)>,
                "math::set::flattening_view must work as a set.");

  CHECK(is_element_of(empty{}, view));
  CHECK_FALSE(is_element_of(0, view));
  CHECK(is_element_of(1, view));
  CHECK(is_element_of(2, view));
  CHECK(is_element_of(3, view));
  CHECK(is_element_of(4, view));
}

TEST_CASE("math::set::is_element_of for flattening_view",
          "[flattening_view][math::set]") {
  std::array<int, 2> a{1, 2};
  std::vector<int> b{3, 4};

  flattening_view view{disjunction, a, b};

  CHECK(set<decltype(view)>);
  CHECK(is_element_of(empty{}, view));
  CHECK_FALSE(is_element_of(0, view));
  CHECK(is_element_of(1, view));
  CHECK(is_element_of(2, view));
  CHECK(is_element_of(3, view));
  CHECK(is_element_of(4, view));
}