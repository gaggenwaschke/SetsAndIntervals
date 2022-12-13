
#pragma once

#include <tuple>

namespace type_traits {
template <typename> struct is_tuple : std::false_type {};

template <typename... TupleElements>
struct is_tuple<std::tuple<TupleElements...>> : std::true_type {};

template <typename Candidate> using is_tuple_v = typename is_tuple<Candidate>::value;
} // namespace type_traits
