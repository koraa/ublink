#pragma once
#include "esp_system.h"
#include "esp_console.h"
#include "esp_vfs_dev.h"
#include "linenoise/linenoise.h"
#include "argtable3/argtable3.h"
#include "driver/uart.h"
#include "esp_vfs_fat.h"
#include <ublink/print.hpp>

namespace ublink {

class console_driver {
public:
  void init() {
    // Disable buffering on stdin
    setvbuf(stdin, NULL, _IONBF, 0);

    uart_port_t port_no = static_cast<uart_port_t>(CONFIG_ESP_CONSOLE_UART_NUM);

    // Install UART driver for interrupt-driven reads and writes
    ESP_ERROR_CHECK(uart_driver_install(port_no, 256, 0, 0, NULL, 0));

    esp_vfs_dev_uart_use_driver(port_no);

    esp_console_config_t console_config;
    console_config.max_cmdline_args = 8;
    console_config.max_cmdline_length = 256;
    ESP_ERROR_CHECK(esp_console_init(&console_config));

    linenoiseSetMultiLine(1);
    linenoiseHistorySetMaxLen(100);
  }

  void tick() {
    char* lineptr = linenoise("ublink $ ");
    if (lineptr == nullptr)
        return;

    linenoiseHistoryAdd(lineptr);

    std::string_view line{lineptr};
    if (line == "relais")
      relais_get();
    else if (line == "relais on")
      relais_on();
    else if (line == "relais off")
      relais_off();
    else
      println("No such command `", line, "`");

    // linenoise allocates line buffer on the heap, so need to free it */
    // TODO: WTF. Can we please use a static buffer
    linenoiseFree(lineptr);
  }

  // Commands

  void relais_get();
  void relais_on();
  void relais_off();
};

}
