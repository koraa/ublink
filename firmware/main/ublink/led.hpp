#pragma once
#include <cmath>
#include <esp_err.h>
#include <driver/ledc.h>
#include "ublink/error.hpp"

namespace ublink {

class led_timer_driver : public ledc_timer_config_t {
public:
  led_timer_driver(
      ledc_timer_t timer, ledc_timer_bit_t resolution,
      uint32_t freq, ledc_mode_t speed=LEDC_HIGH_SPEED_MODE) {

    duty_resolution = resolution;
    freq_hz         = freq;
    speed_mode      = speed;
    timer_num       = timer;

    apply();
  }

  void tick() { /* pass */ }

  void apply() {
    ESP_ERROR_CHECK(ledc_timer_config(this));
  }
};

class led_driver : public ledc_channel_config_t {
public:
	led_timer_driver &timer;

  led_driver(led_timer_driver &timer_, ledc_channel_t chan, int gpio_num_)
			: timer{timer_} {

    channel    = chan;
    duty       = 0;
    gpio_num   = gpio_num_;
    hpoint     = 0;

    apply();
  }

  void tick() { /* pass */ }

	void apply() {
    timer_sel  = timer.timer_num;
    speed_mode = timer.speed_mode;
		ESP_ERROR_CHECK(ledc_channel_config(this));
	}

  uint32_t duty_max() const {
    return (1 << timer.duty_resolution) - 1;
  }

  float duty_frac() const {
    return static_cast<float>(duty) / duty_max();
	}

  void duty_frac(float v) {
    UBLINK_ASSERT(0 >= v && v <= 1, "Parameter to duty_frac() must be ",
      "in the range [0; 1], not ", v);
    duty = round(v * duty_max());
  }
};

}
