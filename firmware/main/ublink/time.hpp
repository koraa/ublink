#pragma once
#include <cstdint>
#include <esp_timer.h>

namespace ublink {

/// Central time keeping
class time_driver {
public:
  uint64_t us_since_start() {
    return esp_timer_get_time();
  }
};

// Forward declare the time driver
extern time_driver time;

/// Microseconds since boot
inline double microsecs() {
  return time.us_since_start();
}

/// Milliseconds since boot
inline double millisecs() {
  return microsecs() / 1000;
}

/// Seconds since boot
inline double secs() {
  return microsecs() / 1000;
}

}
