#pragma once
#include <cstdlib>

namespace ublink {

/// Assert that the given predicate is true;
/// will print the given error message using println()
/// and then call abort if the predicate is false
#define UBLINK_ASSERT(b, ...)                     \
  if (!(b)) {                                     \
    println("[FATAL] ", __VA_ARGS__,              \
            " (", __FILE__, ":", __LINE__, ")");  \
    abort();                                      \
  }

}
