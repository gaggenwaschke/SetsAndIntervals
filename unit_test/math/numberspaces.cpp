
#include <catch2/catch.hpp>
#include <math/numberspaces.hpp>
#include <math/set/set.hpp>

using math::numberspaces::natural;
using math::numberspaces::whole;
using math::numberspaces::integer;
using math::numberspaces::real;

using math::set::is_superset_of;
using math::set::is_element_of;

TEST_CASE("Natural numbers", "[]") {
  CHECK(natural.contains(1));
  CHECK(natural.contains(1.0));
  CHECK(natural.contains(10));
  CHECK(natural.contains(25.0));
  CHECK(natural.contains(1000000));

  CHECK_FALSE(natural.contains(0));
  CHECK_FALSE(natural.contains(0.9999));
  CHECK_FALSE(natural.contains(10.1));

  CHECK_FALSE(natural.contains("Hello"));
  CHECK_FALSE(natural.contains(-1));
  CHECK_FALSE(natural.contains(-1.1));
}

TEST_CASE("Whole numbers", "[]") {
  CHECK(whole.contains(0));
  CHECK(whole.contains(0.0));
  CHECK(whole.contains(1));
  CHECK(whole.contains(1.0));
  CHECK(whole.contains(10));
  CHECK(whole.contains(25.0));
  CHECK(whole.contains(1000000));

  CHECK(is_superset_of(whole, natural));

  CHECK_FALSE(whole.contains(-1));
  CHECK_FALSE(whole.contains(-0.0000000001));
  CHECK_FALSE(whole.contains(10.00001));

  CHECK_FALSE(whole.contains("Hello"));
  CHECK_FALSE(whole.contains(-1.1));
}

TEST_CASE("Integers", "[]") {
  CHECK(integer.contains(-1000000));
  CHECK(integer.contains(-10.0));
  CHECK(integer.contains(-1));
  CHECK(integer.contains(0));
  CHECK(integer.contains(0.0));
  CHECK(integer.contains(1));
  CHECK(integer.contains(1.0));
  CHECK(integer.contains(10));
  CHECK(integer.contains(25.0));
  CHECK(integer.contains(1000000));

  CHECK(is_superset_of(integer, whole));
  CHECK(is_superset_of(integer, natural));
  
  CHECK_FALSE(integer.contains(-0.0000000001));
  CHECK_FALSE(integer.contains(10.00001));

  CHECK_FALSE(integer.contains("Hello"));
  CHECK_FALSE(integer.contains(-1.1));
}

TEST_CASE("Real numbers", "[]") {
  CHECK(real.contains(-1.1));
  CHECK(real.contains(-1));
  CHECK(real.contains(-0.0000000001));
  CHECK(real.contains(0));
  CHECK(real.contains(0.0));
  CHECK(real.contains(1));
  CHECK(real.contains(1.0));
  CHECK(real.contains(10));
  CHECK(real.contains(10.00001));
  CHECK(real.contains(25.0));
  CHECK(real.contains(1000000));

  CHECK(is_superset_of(real, whole));
  CHECK(is_superset_of(real, natural));
  CHECK(is_superset_of(real, integer));

  CHECK_FALSE(real.contains("Hello"));
}

TEST_CASE("is_element_of for number sets", "[]") {
  CHECK(is_element_of(1, natural));
  CHECK_FALSE(is_element_of(0, natural));
  CHECK_FALSE(is_element_of("Hi", natural));

  CHECK(is_element_of(1, real));
  CHECK(is_element_of(10000.0101, real));
  CHECK_FALSE(is_element_of("Hi", real));
}
