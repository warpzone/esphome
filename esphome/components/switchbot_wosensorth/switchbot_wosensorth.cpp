#include "switchbot_wosensorth.h"
#include "esphome/core/log.h"

#ifdef ARDUINO_ARCH_ESP32

namespace esphome {
namespace switchbot_wosensorth {

static const char *TAG = "switchbot_wosensorth";

void SwitchBotWoSensorTH::dump_config() {
  ESP_LOGCONFIG(TAG, "SwitchBot MeterTH");
  LOG_SENSOR("  ", "Temperature", this->temperature_);
  LOG_SENSOR("  ", "Humidity", this->humidity_);
  LOG_SENSOR("  ", "Battery Level", this->battery_level_);
}

}  // namespace switchbot_wosensorth
}  // namespace esphome

#endif
