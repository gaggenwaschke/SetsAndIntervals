
#include <catch2/catch.hpp>
#include <math/set/number.hpp>
#include <math/set/set.hpp>

TEST_CASE("Natural numbers", "[]") {
  CHECK(math::set::number::natural{}.contains(1));
  CHECK(math::set::number::natural{}.contains(1.0));
  CHECK(math::set::number::natural{}.contains(10));
  CHECK(math::set::number::natural{}.contains(25.0));
  CHECK(math::set::number::natural{}.contains(1000000));

  CHECK_FALSE(math::set::number::natural{}.contains(0));
  CHECK_FALSE(math::set::number::natural{}.contains(0.9999));
  CHECK_FALSE(math::set::number::natural{}.contains(10.1));

  CHECK_FALSE(math::set::number::natural{}.contains("Hello"));
  CHECK_FALSE(math::set::number::natural{}.contains(-1));
  CHECK_FALSE(math::set::number::natural{}.contains(-1.1));
}

TEST_CASE("Whole numbers", "[]") {
  CHECK(math::set::number::whole{}.contains(0));
  CHECK(math::set::number::whole{}.contains(0.0));
  CHECK(math::set::number::whole{}.contains(1));
  CHECK(math::set::number::whole{}.contains(1.0));
  CHECK(math::set::number::whole{}.contains(10));
  CHECK(math::set::number::whole{}.contains(25.0));
  CHECK(math::set::number::whole{}.contains(1000000));

  CHECK_FALSE(math::set::number::whole{}.contains(-1));
  CHECK_FALSE(math::set::number::whole{}.contains(-0.0000000001));
  CHECK_FALSE(math::set::number::whole{}.contains(10.00001));

  CHECK_FALSE(math::set::number::whole{}.contains("Hello"));
  CHECK_FALSE(math::set::number::whole{}.contains(-1.1));
}

TEST_CASE("Integers", "[]") {
  CHECK(math::set::number::integers{}.contains(-1000000));
  CHECK(math::set::number::integers{}.contains(-10.0));
  CHECK(math::set::number::integers{}.contains(-1));
  CHECK(math::set::number::integers{}.contains(0));
  CHECK(math::set::number::integers{}.contains(0.0));
  CHECK(math::set::number::integers{}.contains(1));
  CHECK(math::set::number::integers{}.contains(1.0));
  CHECK(math::set::number::integers{}.contains(10));
  CHECK(math::set::number::integers{}.contains(25.0));
  CHECK(math::set::number::integers{}.contains(1000000));

  CHECK_FALSE(math::set::number::integers{}.contains(-0.0000000001));
  CHECK_FALSE(math::set::number::integers{}.contains(10.00001));

  CHECK_FALSE(math::set::number::integers{}.contains("Hello"));
  CHECK_FALSE(math::set::number::integers{}.contains(-1.1));
}

TEST_CASE("Real numbers", "[]") {
  CHECK(math::set::number::real{}.contains(-1.1));
  CHECK(math::set::number::real{}.contains(-1));
  CHECK(math::set::number::real{}.contains(-0.0000000001));
  CHECK(math::set::number::real{}.contains(0));
  CHECK(math::set::number::real{}.contains(0.0));
  CHECK(math::set::number::real{}.contains(1));
  CHECK(math::set::number::real{}.contains(1.0));
  CHECK(math::set::number::real{}.contains(10));
  CHECK(math::set::number::real{}.contains(10.00001));
  CHECK(math::set::number::real{}.contains(25.0));
  CHECK(math::set::number::real{}.contains(1000000));

  CHECK_FALSE(math::set::number::real{}.contains("Hello"));
}

TEST_CASE("math::set::is_element_of for number sets", "[]") {
  CHECK(math::set::is_element_of(1, math::set::number::natural{}));
  CHECK_FALSE(math::set::is_element_of(0, math::set::number::natural{}));
  CHECK_FALSE(math::set::is_element_of("Hi", math::set::number::natural{}));

  CHECK(math::set::is_element_of(1, math::set::number::real{}));
  CHECK(math::set::is_element_of(10000.0101, math::set::number::real{}));
  CHECK_FALSE(math::set::is_element_of("Hi", math::set::number::real{}));
}
