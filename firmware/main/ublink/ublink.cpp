#include <unistd.h>
#include <cmath>
#include "ublink/print.hpp"
#include "ublink/time.hpp"
#include "ublink/relais.hpp"
#include "ublink/led.hpp"

namespace ublink {

// Drivers/Subsystems; using classes for these instead of plain
// functions/globals has a couple of advantages:
//
// 1. Some drivers (like the led ones for instance) can actually be reused
// 2. By injecting the configuration here, one can get a good introduction
//    as to how this firmware is structured
// 3. Constructors/destructors can be used for initialization/deinit without
//    extra code
// 4. We can have globals this way, while avoiding the initialization order fiasco
// 5. Each driver provides a hardware abstraction point; just use a different driver
//    for different hardware; generally the drivers should provide an opaque, portable
//    interface

time_driver time;
relais_driver relais{GPIO_NUM_23};
led_timer_driver led_timer{LEDC_TIMER_0, LEDC_TIMER_12_BIT, 10000};
led_pwm_driver led_r{led_timer, LEDC_CHANNEL_0, GPIO_NUM_2};

void tick() {}

/// Just calls .tick() on each parameter left-to-right. For convenience
template<typename T, typename... Args>
void tick(T &fst, Args&&... rest) {
  fst.tick();
  tick(std::forward<Args>(rest)...);
}

/// Produce the color for the RGBW led
void render() {
  const auto secs = time.us_since_start() / float{1000000};
  led_r.duty_frac(sin(secs) / 2 + 0.5);
  led_r.apply();
}

extern "C" void app_main() {
  println("µBlink Firmware Version 0.0.1");

  while (true) {
    tick(time, relais, led_timer, led_r);
    render();
  }
}

}
#include <cmath>
