#include "ublink/print.hpp"
#include "ublink/console.hpp"
#include "ublink/ublink.hpp"

namespace ublink {

void console_driver::relais_get() {
  println("Relais is ", relais.powered() ? "on" : "off");
}

void console_driver::relais_on() {
  relais.powered(true);
}

void console_driver::relais_off() {
  relais.powered(false);
}

}
