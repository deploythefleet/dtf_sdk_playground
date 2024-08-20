#include <stdio.h>
#include <thread>
#include <chrono>

extern "C" void app_main(void)
{
  while (true) {
      printf("Welcome to the DTF SDK Playground\n");
      std::this_thread::sleep_for(std::chrono::seconds{5});
  }
}