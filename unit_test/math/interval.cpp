
#include <catch2/catch.hpp>
#include <math/interval.hpp>
#include <math/numberspaces.hpp>
#include <math/set/empty.hpp>
#include <math/set/set.hpp>

using math::interval;
using math::numberspaces::integer;
using math::numberspaces::natural;
using math::numberspaces::real;
using math::numberspaces::whole;
using math::set::empty;
using math::set::is_element_of;
using math::set::is_subset_of;
using math::set::set;

namespace mock {
struct NonComparable {};
} // namespace mock

TEST_CASE("math::interval<int>", "[]") {
  using interval_type = interval<int>;

  static_assert(
      std::random_access_iterator<std::ranges::iterator_t<interval_type>>);
  static_assert(std::ranges::range<interval_type>);

  interval_type interval{1, 3};

  CHECK(set<decltype(interval)>);
  CHECK(interval.contains(empty{}));
  CHECK_FALSE(interval.contains(0));
  CHECK(interval.contains(1));
  CHECK(interval.contains(2));
  CHECK_FALSE(interval.contains(3));
}

TEST_CASE("is_element_of for intervals", "[]") {
  math::interval interval{1, 3};

  CHECK(set<decltype(interval)>);
  CHECK(is_element_of(empty{}, interval));
  CHECK_FALSE(is_element_of(0, interval));
  CHECK(is_element_of(1, interval));
  CHECK(is_element_of(2, interval));
  CHECK_FALSE(is_element_of(3, interval));
  CHECK_FALSE(is_element_of(mock::NonComparable{}, interval));
}

TEST_CASE("is_subset_of for intervals", "[]") {
  std::tuple superset{"hello", 2, 4, 1};
  math::interval inner_interval{1, 2};
  math::interval outer_interval{1, 5};
  math::interval non_natural_interval{0, 4};
  math::interval non_whole_interval{-1, 1};
  math::interval floating_interval{-1.0, 1.0};

  CHECK(is_subset_of(inner_interval, superset));
  CHECK(is_subset_of(inner_interval, outer_interval));
  CHECK(is_subset_of(inner_interval, natural));
  CHECK(is_subset_of(non_natural_interval, whole));
  CHECK(is_subset_of(non_whole_interval, integer));
  CHECK(is_subset_of(floating_interval, real));

  CHECK_FALSE(is_subset_of(outer_interval, superset));
  CHECK_FALSE(is_subset_of(outer_interval, inner_interval));
  CHECK_FALSE(is_subset_of(non_natural_interval, natural));
  CHECK_FALSE(is_subset_of(non_whole_interval, whole));
  CHECK_FALSE(is_subset_of(floating_interval, integer));
}
