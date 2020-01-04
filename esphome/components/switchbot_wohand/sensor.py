import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, esp32_ble_tracker
from esphome.const import CONF_BATTERY_LEVEL, CONF_MAC_ADDRESS, \
    UNIT_PERCENT, ICON_BATTERY, CONF_ID

DEPENDENCIES = ['esp32_ble_tracker']
AUTO_LOAD = ['switchbot_ble']

switchbot_wohand_ns = cg.esphome_ns.namespace('switchbot_wohand')
SwitchBotWoHand = switchbot_wohand_ns.class_(
    'SwitchBotWoHand', esp32_ble_tracker.ESPBTDeviceListener, cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SwitchBotWoHand),
    cv.Required(CONF_MAC_ADDRESS): cv.mac_address,
    cv.Optional(CONF_BATTERY_LEVEL): sensor.sensor_schema(UNIT_PERCENT, ICON_BATTERY, 0),
}).extend(esp32_ble_tracker.ESP_BLE_DEVICE_SCHEMA).extend(cv.COMPONENT_SCHEMA)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield esp32_ble_tracker.register_ble_device(var, config)

    cg.add(var.set_address(config[CONF_MAC_ADDRESS].as_hex))

    if CONF_BATTERY_LEVEL in config:
        sens = yield sensor.new_sensor(config[CONF_BATTERY_LEVEL])
        cg.add(var.set_battery_level(sens))
