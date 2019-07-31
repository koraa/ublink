#pragma once
#include <cstdlib>

namespace ublink {

#pragma once
#define UBLINK_ASSERT(b, ...)                     \
  if (!(b)) {                                     \
    println("[FATAL] ", __VA_ARGS__,              \
            " (", __FILE__, ":", __LINE__, ")");  \
    abort();                                      \
  }

}
