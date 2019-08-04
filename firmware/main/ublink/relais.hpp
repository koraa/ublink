#pragma once
#include <esp_err.h>
#include <driver/gpio.h>

namespace ublink {

/// This is pretty much just a wrapper around a gpio;
/// turns the relais on/off (usually to activate/deactivate
/// the external LED power supply)
class relais_driver {
public:
  const gpio_num_t gpio;
  bool powered_;

  relais_driver(gpio_num_t gpio_) : gpio{gpio_} {
    ESP_ERROR_CHECK(gpio_intr_disable(gpio));
    ESP_ERROR_CHECK(gpio_set_direction(gpio, GPIO_MODE_OUTPUT));
    powered(false);
  }

  bool powered() const {
    return powered_;
  }

  void powered(bool on) {
    powered_ = on;
    ESP_ERROR_CHECK(gpio_set_level(gpio, on));
  }
};

}
