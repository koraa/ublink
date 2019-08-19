#include "ublink/print.hpp"
#include "ublink/console.hpp"
#include "ublink/ublink.hpp"

namespace ublink {

void console_driver::relais_get() {
  println("Relais is ", relais.get() ? "on" : "off");
}

void console_driver::relais_on() {
  relais.set(true);
}

void console_driver::relais_off() {
  relais.set(false);
}

void console_driver::reset() {
  ::ublink::reset();
}

void console_driver::reset_uart_download() {
  ::ublink::reset_uart_download();
}

}
