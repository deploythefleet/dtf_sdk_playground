#include <stdio.h>
#include <thread>
#include <chrono>
#include "dtf_logging.h"

extern "C" void app_main(void)
{
  dtf_set_log_level(INFO);

  while (true) {
      DTF_LOGI("main", "Welcome to the DTF SDK Playground!");
      std::this_thread::sleep_for(std::chrono::seconds{5});
  }
}