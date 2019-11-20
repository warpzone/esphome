#include "switchbot_hand.h"
#include "esphome/core/log.h"

#ifdef ARDUINO_ARCH_ESP32

namespace esphome {
namespace switchbot_hand {

static const char *TAG = "switchbot_hand";

void SwitchBotHand::dump_config() {
  ESP_LOGCONFIG(TAG, "SwitchBot Hand");
  LOG_SENSOR("  ", "Battery Level", this->battery_level_);
}

}  // namespace switchbot_hand
}  // namespace esphome

#endif
