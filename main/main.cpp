#include <stdio.h>
#include <thread>
#include <chrono>
#include <esp_event.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_netif.h"
#include "nvs_flash.h"
#include "dtf_logging.h"
#include "dtf_ota.h"
#include "wifi_connect.h"

extern "C" void app_main(void)
{
  DTF_LOGI("main", "Welcome to the DTF SDK Playground!");

  DTF_LOGI("main", "Setting log level to INFO");
  dtf_set_log_level(INFO);

  // Initialize NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  DTF_LOGI("main", "Connecting to WiFi\n");

  connect_to_wifi();

  const dtf_ota_cfg_t cfg = {
      .product_id = CONFIG_DTF_PLAYGROUND_PRODUCT_ID,
      .reboot_option = DTF_NO_REBOOT};

  if (is_wifi_connected())
  {
    DTF_LOGI("main", "Checking for updates from Deploy the Fleet");
    auto ret = dtf_get_firmware_update(&cfg);
    DTF_LOGI("main", "Firmware update response: %d", ret);
  }
  else
  {
    DTF_LOGW("main", "Not connected to WiFi. Skipping firmware update check.");
  }

  while (true) {
    DTF_LOGI("main", "Current firmware version: %s", dtf_get_active_fw_version());
    std::this_thread::sleep_for(std::chrono::seconds{5});
  }
}