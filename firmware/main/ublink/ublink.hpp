/// Mostly declaration of globals
#pragma once
#include <tuple>
#include "ublink/console.hpp"
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

#ifdef UBLINK_GLOBAL_STORE
  // Declare & initialize globals
  #define STORAGE
  #define INIT(...) {__VA_ARGS__}
#else
  #define STORAGE extern
  #define INIT(...)
#endif


STORAGE console_driver console;
STORAGE time_driver time;
STORAGE relais_driver relais INIT(GPIO_NUM_23);
STORAGE led_timer_driver led_timer INIT(LEDC_TIMER_0, LEDC_TIMER_12_BIT, 10000);
STORAGE led_pwm_driver led_r INIT(led_timer, LEDC_CHANNEL_0, GPIO_NUM_2);

#undef STORAGE
#undef INIT

inline auto drivers() {
  return std::tie(console, time, relais, led_timer, led_r);
}

}
