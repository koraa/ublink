#include <stdio.h>
#include <unistd.h>

extern "C" void app_main() {
  for (size_t i=0; true; i++) {
    printf("Hello world! %zi\n", i);
    sleep(1);
  }
}
