#pragma once
#include <cmath>
#include <esp_err.h>
#include <driver/ledc.h>
#include "ublink/error.hpp"

namespace ublink {

/// Each LED PWM Driver needs a timer; all low speed channels
/// may share one timer while all high speed channels may share
/// another.
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

  /// Call this to apply any changes made to the timer configuration
  /// If timer_num or speed_mode have been changed, apply() should be
  /// called on all led pwm drivers too
  void apply() {
    ESP_ERROR_CHECK(ledc_timer_config(this));
  }
};

/// Controls a single LED using PWM
class led_pwm_driver : public ledc_channel_config_t {
public:
	led_timer_driver &timer;

  led_pwm_driver(led_timer_driver &timer_, ledc_channel_t chan, int gpio_num_)
			: timer{timer_} {

    channel    = chan;
    duty       = 0;
    gpio_num   = gpio_num_;
    hpoint     = 0;

    apply();
  }

  void tick() { /* pass */ }

  /// Call this to apply any changes made to the led pwm channel config
	void apply() {
    timer_sel  = timer.timer_num;
    speed_mode = timer.speed_mode;
		ESP_ERROR_CHECK(ledc_channel_config(this));
	}

  /// Maximum for the raw duty value
  uint32_t duty_max() const {
    return (1 << timer.duty_resolution) - 1;
  }

  /// Get the duty as a float in [0; 1] where 0 is off and 1 is maximum brightness
  float duty_frac() const {
    return static_cast<float>(duty) / duty_max();
	}

  /// Set the duty cycle as a fraction [0; 1]
  void duty_frac(float v) {
    UBLINK_ASSERT(0.0 <= v && v <= 1.0, "Parameter to duty_frac() must be ",
      "in the range [0; 1], not ", v);
    duty = round(v * duty_max());
  }
};

}
