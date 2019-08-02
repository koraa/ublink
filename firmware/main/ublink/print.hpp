#pragma once
#include <iostream>
#include <type_traits>

namespace ublink {

template<typename T, typename Enable=void>
struct print_trait {

  template<typename U>
  static void print(U &&v) {
    std::cout << std::forward<T>(v);
  }
};

constexpr auto ret = '\n';

struct flush_t {} constexpr flush;

template<>
struct print_trait<flush_t> {
  static void print(flush_t&&) {
    std::cout << std::flush;
  }
};

inline void print() {}

/// Just forwards to std::cout but with a more convenient syntax
template<typename T, typename... Args>
void print(T &&v, Args&&... args) {
  print_trait<T>::print(std::forward<T>(v));
  print(std::forward<Args>(args)...);
}

/// Just forwards to std::cout but with a more convenient syntax and a new line
template<typename... Args>
void println(Args&&... args) {
  print(std::forward<Args>(args)..., ret);
}


}
