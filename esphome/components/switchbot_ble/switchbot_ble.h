#pragma once

#include "esphome/core/component.h"
#include "esphome/components/esp32_ble_tracker/esp32_ble_tracker.h"

#ifdef ARDUINO_ARCH_ESP32

namespace esphome {
namespace switchbot_ble {

struct SwitchBotParseResult {
  enum { TYPE_HAND, TYPE_METER } type;
  optional<float> temperature;
  optional<uint8_t> humidity;
  optional<uint8_t> battery_level;
};

bool parse_switchbot_data_byte(uint8_t data_type, const uint8_t *data, uint8_t data_length, SwitchBotParseResult &result);

optional<SwitchBotParseResult> parse_switchbot(const esp32_ble_tracker::ESPBTDevice &device);

class SwitchBotListener : public esp32_ble_tracker::ESPBTDeviceListener {
 public:
  bool parse_device(const esp32_ble_tracker::ESPBTDevice &device) override;
};

}  // namespace switchbot_ble
}  // namespace esphome

#endif
