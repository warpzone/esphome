#include "switchbot_meter.h"
#include "esphome/core/log.h"

#ifdef ARDUINO_ARCH_ESP32

namespace esphome {
namespace switchbot_meter {

static const char *TAG = "switchbot_meter";

void SwitchBotMeter::dump_config() {
  ESP_LOGCONFIG(TAG, "SwitchBot Meter");
  LOG_SENSOR("  ", "Temperature", this->temperature_);
  LOG_SENSOR("  ", "Humidity", this->humidity_);
  LOG_SENSOR("  ", "Battery Level", this->battery_level_);
}

}  // namespace switchbot_meter
}  // namespace esphome

#endif
