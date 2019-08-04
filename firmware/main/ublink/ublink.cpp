// Actually declare driver globals in this file
#define UBLINK_GLOBAL_STORE 1
#include <unistd.h>
#include <cmath>
#include <tuple>
#include "ublink/meta.hpp"
#include "ublink/print.hpp"
#include "ublink/ublink.hpp"

namespace ublink {

DECLARE_METHOD_CHECK(driver_supports_init, init);
DECLARE_METHOD_CHECK(driver_supports_tick, tick);

inline void init_drivers() {
  tuple_each(drivers(), [](size_t, auto &t){
    if constexpr (driver_supports_init<decltype(t)>)
      t.init();
  });
}

inline void tick_drivers() {
  tuple_each(drivers(), [](size_t, auto &t){
    if constexpr (driver_supports_tick<decltype(t)>)
      t.tick();
  });
}

/// Produce the color for the RGBW led
inline void render() {
  led_r.duty_frac(sin(secs()) / 2 + 0.5);
  led_r.apply();
}

extern "C" void app_main() {
  println("µBlink Firmware Version 0.0.1");
  init_drivers();

  while (true) {
    tick_drivers();
    render();
  }
}

}
#include <cmath>
