#include <catch2/catch_template_test_macros.hpp>
#include <iterator>
#include <math/integral_iterator.hpp>

TEMPLATE_TEST_CASE("math::integral_iterator is an iterator", "[math]",
                   std::int8_t, std::int32_t, std::int64_t, int) {
  static_assert(std::random_access_iterator<math::integral_iterator<TestType>>);
}
