import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components.light.types import AddressableLightEffect
from esphome.components.light.effects import register_addressable_effect

from esphome.const import (
    CONF_NAME,
    CONF_UPDATE_INTERVAL,
    CONF_RED,
    CONF_GREEN,
    CONF_BLUE,
    CONF_WHITE,
)

CONF_COLOR = "color"

CONF_STARS_PROBABILITY = "stars_probability"
CONF_CHRISTMASS_BIT_SIZE = "bit_size"
CONF_CHRISTMASS_BLANK_SIZE = "blank_size"

CONF_HEARTBEAT_BPM = "bpm"

light_ns = cg.esphome_ns.namespace("light")
ColorStruct = cg.esphome_ns.struct("Color")

AddressableStarsEffect = light_ns.class_("AddressableStarsEffect", AddressableLightEffect)
AddressableChristmasEffect = light_ns.class_("AddressableChristmasEffect", AddressableLightEffect)
AddressableHeartbeatEffect = light_ns.class_("AddressableHeartbeatEffect", AddressableLightEffect)


#CONFIG_SCHEMA = cv.All(cv.Schema({}), cv.only_with_arduino)

@register_addressable_effect(
    "addressable_stars",
    AddressableStarsEffect,
    "Stars",
    {
        cv.Optional(CONF_STARS_PROBABILITY, default="10%"): cv.percentage,
        cv.Optional(
            CONF_COLOR, default={CONF_RED: 0.0,CONF_GREEN: 0.0, CONF_BLUE:0.0},
        ): cv.Schema(
            {
                cv.Optional(CONF_RED, default=0): cv.percentage,
                cv.Optional(CONF_GREEN, default=0): cv.percentage,
                cv.Optional(CONF_BLUE, default=0): cv.percentage,
                cv.Optional(CONF_WHITE, default=0): cv.percentage,
            }
           ),
    },
)
async def addressable_stars_effect_to_code(config, effect_id):
    var = cg.new_Pvariable(effect_id, config[CONF_NAME])
    cg.add(var.set_stars_probability(config[CONF_STARS_PROBABILITY]))
    color_conf = config[CONF_COLOR]
    color = cg.StructInitializer(
                ColorStruct,
                ("r", int(round(color_conf[CONF_RED] * 255))),
                ("g", int(round(color_conf[CONF_GREEN] * 255))),
                ("b", int(round(color_conf[CONF_BLUE] * 255))),
                ("w", int(round(color_conf[CONF_WHITE] * 255))),
            )
    cg.add(var.set_color(color))
    return var

@register_addressable_effect(
    "addressable_christmas",
    AddressableChristmasEffect,
    "Christmas",
    {
        cv.Optional(CONF_CHRISTMASS_BIT_SIZE, default="1"): cv.uint8_t,
        cv.Optional(CONF_CHRISTMASS_BLANK_SIZE, default="0"): cv.uint8_t,
    },

)
async def addressable_christmas_effect_to_code(config, effect_id):
    var = cg.new_Pvariable(effect_id, config[CONF_NAME])
    cg.add(var.set_bit_size(config[CONF_CHRISTMASS_BIT_SIZE]))
    cg.add(var.set_blank_size(config[CONF_CHRISTMASS_BLANK_SIZE]))
    return var

@register_addressable_effect(
    "addressable_heartbeat",
    AddressableHeartbeatEffect,
    "Heartbeat",
    {
        cv.Optional(
            CONF_UPDATE_INTERVAL, default="16ms"
        ): cv.positive_time_period_milliseconds,
        cv.Optional(CONF_HEARTBEAT_BPM, default="40"): cv.uint8_t,
    },

)
async def addressable_christmas_effect_to_code(config, effect_id):
    var = cg.new_Pvariable(effect_id, config[CONF_NAME])
    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))
    cg.add(var.set_bpm(config[CONF_HEARTBEAT_BPM]))
    return var