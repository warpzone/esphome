import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import esp32_ble_tracker
from esphome.const import CONF_ID

DEPENDENCIES = ['esp32_ble_tracker']

switchbot_ble_ns = cg.esphome_ns.namespace('switchbot_ble')
SwitchBotListener = switchbot_ble_ns.class_('SwitchBotListener', esp32_ble_tracker.ESPBTDeviceListener)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SwitchBotListener),
}).extend(esp32_ble_tracker.ESP_BLE_DEVICE_SCHEMA)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield esp32_ble_tracker.register_ble_device(var, config)
