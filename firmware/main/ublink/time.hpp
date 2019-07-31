#pragma once
#include <cstdint>
#include <esp_timer.h>

namespace ublink {

class time_driver {
public:

  void tick() { /* pass */ }

  uint64_t us_since_start() {
    return esp_timer_get_time();
  }

};

}
