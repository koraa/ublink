#include <unistd.h>
#include "ublink/print.hpp"
#include "ublink/time.hpp"
#include "ublink/relais.hpp"
#include "ublink/led.hpp"

namespace ublink {

time_driver time;
relais_driver relais{GPIO_NUM_23};
led_timer_driver led_timer{LEDC_TIMER_0, LEDC_TIMER_12_BIT, 10000};
led_driver led_r{led_timer, LEDC_CHANNEL_0, GPIO_NUM_2};

void tick() {}

template<typename T, typename... Args>
void tick(T &fst, Args&&... rest) {
  fst.tick();
  tick(std::forward<Args>(rest)...);
}

extern "C" void app_main() {
  println("µBlink Firmware Version 0.0.1");

  while (true) {
    tick(time, relais, led_timer, led_r);

    led_r.duty_frac(time.us_since_start() / float{1000000});
    led_r.apply();
  }
}

}
