#include "switchbot_wohand.h"
#include "esphome/core/log.h"

#ifdef ARDUINO_ARCH_ESP32

namespace esphome {
namespace switchbot_wohand {

static const char *TAG = "switchbot_wohand";

void SwitchBotWoHand::dump_config() {
  ESP_LOGCONFIG(TAG, "SwitchBot Bot");
  LOG_SENSOR("  ", "Battery Level", this->battery_level_);
}

}  // namespace switchbot_wohand
}  // namespace esphome

#endif
