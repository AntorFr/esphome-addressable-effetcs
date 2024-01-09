#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "esphome/components/light/light_output.h"

namespace esphome {
namespace template_ {

class TemplateLight : public light::LightOutput, public Component {
 public:
  TemplateSwitch();

  void dump_config() override;

  void set_state_lambda(std::function<optional<bool>()> &&f);
  Trigger<> *get_turn_on_trigger() const;
  Trigger<> *get_turn_off_trigger() const;
  void set_optimistic(bool optimistic);
  void loop() override;

  light::LightTraits get_traits() override {
    auto traits = light::LightTraits();
    traits.set_supported_color_modes({light::ColorMode::ON_OFF, ColorMode::BRIGHTNESS, light::ColorMode::RGB});
    return traits;
  }

  float get_setup_priority() const override;

 protected:
  bool assumed_state() override;

  void write_state(light::LightState *state) override;

  optional<std::function<optional<bool>()>> f_;
  bool optimistic_{false};
  Trigger<> *turn_on_trigger_;
  Trigger<> *turn_off_trigger_;
  Trigger<> *prev_trigger_{nullptr};
};

}  // namespace template_
}  // namespace esphome

