import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components.light.types import AddressableLightEffect
from esphome.components.light.effects import register_addressable_effect

from esphome.const import (
    CONF_NAME
)

CONF_STARS_PROBABILITY = "stars_probability"
CONF_FPS = "fps"

light_ns = cg.esphome_ns.namespace("light")
AddressableStarsEffect = light_ns.class_("AddressableStarsEffect", AddressableLightEffect)

CONFIG_SCHEMA = cv.All(cv.Schema({}), cv.only_with_arduino)

@register_addressable_effect(
    "addressable_stars",
    AddressableStarsEffect,
    "Stars",
    {
        cv.Optional(CONF_STARS_PROBABILITY, default="0.1%"): cv.percentage,
        cv.Optional(CONF_FPS, default=60): cv.uint8_t,
    },
)
async def addressable_stars_effect_to_code(config, effect_id):
    var = cg.new_Pvariable(effect_id, config[CONF_NAME])
    cg.add(var.set_stars_probability(config[CONF_STARS_PROBABILITY]))
    cg.add(var.set_fps(config[CONF_FPS]))
    return var
