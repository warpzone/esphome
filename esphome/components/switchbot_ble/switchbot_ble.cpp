#include "switchbot_ble.h"
#include "esphome/core/log.h"

#ifdef ARDUINO_ARCH_ESP32

namespace esphome {
namespace switchbot_ble {

static const char *TAG = "switchbot_ble";

optional<SwitchBotParseResult> parse_switchbot(const esp32_ble_tracker::ESPBTDevice &device) {
  if (!device.get_service_data_uuid().has_value()) {
    ESP_LOGVV(TAG, "SwitchBot no service data");
    return {};
  }

  if (!device.get_service_data_uuid()->contains(0x00, 0x0D)) {
    ESP_LOGVV(TAG, "SwitchBot no service data UUID magic bytes");
    return {};
  }

  const auto *raw = reinterpret_cast<const uint8_t *>(device.get_service_data().data());

  if (device.get_service_data().size() < 3) {
    // ESP_LOGVV(TAG, "SwitchBot service data too short!");
    return {};
  }

  bool is_hand  = (raw[0] & 0x7f) == 0x48;
  bool is_meter = (raw[0] & 0x7f) == 0x54;

  if (!is_hand && !is_meter) {
    // ESP_LOGVV(TAG, "SwitchBot no magic bytes");
    return {};
  }

  SwitchBotParseResult result;
  result.type = SwitchBotParseResult::TYPE_HAND;
  if (is_meter) {
    result.type = SwitchBotParseResult::TYPE_METER;
  }

  result.battery_level = raw[2] & 0x7f;

  if (is_meter) {
    result.humidity = raw[5] & 0x7f;
    if ( (raw[5] & 0x80) >> 7 ) {
      result.temperature = (raw[4] & 0x7f) + (raw[3] & 0xf0) / 10.0f;
    } else {
      result.temperature = (raw[4] & 0x7f) + (raw[3] & 0xf0) / 10.0f * (-1);
    }
  }

  return result;
}

bool SwitchBotListener::parse_device(const esp32_ble_tracker::ESPBTDevice &device) {
  auto res = parse_switchbot(device);
  if (!res.has_value())
    return false;

  const char *name = "Hand";
  if (res->type == SwitchBotParseResult::TYPE_METER) {
    name = "Meter";
  }

  ESP_LOGD(TAG, "Got SwitchBot %s (%s):", name, device.address_str().c_str());

  if (res->temperature.has_value()) {
    ESP_LOGD(TAG, "  Temperature: %.1f°C", *res->temperature);
  }
  if (res->humidity.has_value()) {
    ESP_LOGD(TAG, "  Humidity: %u%%", *res->humidity);
  }
  if (res->battery_level.has_value()) {
    ESP_LOGD(TAG, "  Battery Level: %u%%", *res->battery_level);
  }

  return true;
}

}  // namespace switchbot_ble
}  // namespace esphome

#endif
