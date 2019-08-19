#pragma once
#include <esp_err.h>
#include <driver/gpio.h>

namespace ublink {

/// This is pretty much just a wrapper around a gpio;
/// turns the relais on/off (usually to activate/deactivate
/// the external LED power supply)
class gpio_out {
public:
  const gpio_num_t gpio;
  bool value;

  gpio_out(gpio_num_t gpio_, bool initial) : gpio{gpio_} {
    ESP_ERROR_CHECK(gpio_set_pull_mode(gpio, GPIO_PULLUP_ONLY));
    ESP_ERROR_CHECK(gpio_set_direction(gpio, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_intr_disable(gpio));
    set(initial);
  }

  bool get() const {
    return value;
  }

  void set(bool val) {
    value = val;
    ESP_ERROR_CHECK(gpio_set_level(gpio, val));
  }
};

}
