/// Metaprogramming helpers
#pragma once
#include <tuple>
#include <type_traits>

namespace ublink {

/// Use to declare a type trait testing for the existence of a
/// method inside a class
#define DECLARE_METHOD_CHECK(check_name, method_name)       \
  inline auto check_name ## _impl_(...) -> std::false_type; \
                                                            \
  template<typename T>                                      \
  inline auto check_name ## _impl_(T v)                     \
    -> decltype(v. method_name (), std::true_type{});       \
                                                            \
  template<typename T>                                      \
  constexpr bool check_name = decltype(                     \
      check_name ## _impl_(std::declval<T>()))::value;

/// Iterate over each element in a tuple
template<size_t Index=0, typename Tuple, typename Fn>
void tuple_each(Tuple &&tup, Fn &&fn) {
  if constexpr (Index < std::tuple_size_v<std::decay_t<Tuple>>) {
    fn(Index, std::get<Index>(tup));
    tuple_each<Index+1>(tup, fn);
  }
}

}
