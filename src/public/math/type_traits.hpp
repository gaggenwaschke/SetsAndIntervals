
#pragma once

#include <tuple>

namespace type_traits {
template <class Candidate, std::size_t = sizeof(Candidate)>
std::true_type is_complete_impl(Candidate *);

std::false_type is_complete_impl(...);

template <class Candidate>
using is_complete = decltype(is_complete_impl(std::declval<Candidate *>()));

template <class Candidate>
using is_complete_v = typename is_complete<Candidate>::value;

template <typename> struct is_tuple : std::false_type {};

template <typename... TupleElements>
struct is_tuple<std::tuple<TupleElements...>> : std::true_type {};

template <typename Candidate>
using is_tuple_v = typename is_tuple<Candidate>::value;
} // namespace type_traits
