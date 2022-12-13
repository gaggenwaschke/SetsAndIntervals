
#include <catch2/catch.hpp>
#include <math/infinity.hpp>
#include <math/numberspaces.hpp>
#include <math/set.hpp>

using namespace math::numberspaces;
using namespace math::set;

TEST_CASE("Natural numbers", "[]") {
  static_assert(std::ranges::range<natural_type>);

  CHECK(get_cardinality(natural) == math::infinity);
  CHECK(is_infinite<natural_type>);

  CHECK(is_countable(natural));

  CHECK(is_element_of(1, natural));
  CHECK(is_element_of(1.0, natural));
  CHECK(is_element_of(10, natural));
  CHECK(is_element_of(25.0, natural));
  CHECK(is_element_of(1000000, natural));

  CHECK_FALSE(is_element_of(0, natural));
  CHECK_FALSE(is_element_of(0.9999, natural));
  CHECK_FALSE(is_element_of(10.1, natural));

  CHECK_FALSE(is_element_of("Hello", natural));
  CHECK_FALSE(is_element_of(-1, natural));
  CHECK_FALSE(is_element_of(-1.1, natural));
}

TEST_CASE("Whole numbers", "[]") {
  CHECK(get_cardinality(whole) == math::infinity);
  CHECK(is_infinite<whole_type>);

  CHECK(is_countable(whole));

  CHECK(is_element_of(0, whole));
  CHECK(is_element_of(0.0, whole));
  CHECK(is_element_of(1, whole));
  CHECK(is_element_of(1.0, whole));
  CHECK(is_element_of(10, whole));
  CHECK(is_element_of(25.0, whole));
  CHECK(is_element_of(1000000, whole));

  CHECK(is_superset_of(whole, natural));

  CHECK_FALSE(is_element_of(-1, whole));
  CHECK_FALSE(is_element_of(-0.0000000001, whole));
  CHECK_FALSE(is_element_of(10.00001, whole));

  CHECK_FALSE(is_element_of("Hello", whole));
  CHECK_FALSE(is_element_of(-1.1, whole));
}

TEST_CASE("Integers", "[]") {
  CHECK(get_cardinality(integer) == math::infinity);
  CHECK(is_infinite<integer_type>);

  CHECK(is_countable(integer));

  CHECK(is_element_of(-1000000, integer));
  CHECK(is_element_of(-10.0, integer));
  CHECK(is_element_of(-1, integer));
  CHECK(is_element_of(0, integer));
  CHECK(is_element_of(0.0, integer));
  CHECK(is_element_of(1, integer));
  CHECK(is_element_of(1.0, integer));
  CHECK(is_element_of(10, integer));
  CHECK(is_element_of(25.0, integer));
  CHECK(is_element_of(1000000, integer));

  CHECK(is_superset_of(integer, whole));
  CHECK(is_superset_of(integer, natural));

  CHECK_FALSE(is_element_of(-0.0000000001, integer));
  CHECK_FALSE(is_element_of(10.00001, integer));

  CHECK_FALSE(is_element_of("Hello", integer));
  CHECK_FALSE(is_element_of(-1.1, integer));
}

TEST_CASE("Real numbers", "[]") {
  CHECK(get_cardinality(real) == math::infinity);
  CHECK(is_infinite<real_type>);

  CHECK_FALSE(is_countable(real));

  CHECK(is_element_of(-1.1, real));
  CHECK(is_element_of(-1, real));
  CHECK(is_element_of(-0.0000000001, real));
  CHECK(is_element_of(0, real));
  CHECK(is_element_of(0.0, real));
  CHECK(is_element_of(1, real));
  CHECK(is_element_of(1.0, real));
  CHECK(is_element_of(10, real));
  CHECK(is_element_of(10.00001, real));
  CHECK(is_element_of(25.0, real));
  CHECK(is_element_of(1000000, real));

  CHECK(is_superset_of(real, whole));
  CHECK(is_superset_of(real, natural));
  CHECK(is_superset_of(real, integer));

  CHECK_FALSE(is_element_of("Hello", real));
}
