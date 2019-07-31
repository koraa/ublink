#pragma once
#include <esp_err.h>
#include <driver/gpio.h>

namespace ublink {

class relais_driver {
public:
  const gpio_num_t gpio;

  relais_driver(gpio_num_t gpio_) : gpio{gpio_} {
    ESP_ERROR_CHECK(gpio_intr_disable(gpio));
    ESP_ERROR_CHECK(gpio_set_direction(gpio, GPIO_MODE_OUTPUT));
    powered(false);
  }

  void tick() { /* pass */ }

  bool powered() const {
    return gpio_get_level(gpio);
  }

  void powered(bool on) {
    ESP_ERROR_CHECK(gpio_set_level(gpio, on));
  }
};

}
