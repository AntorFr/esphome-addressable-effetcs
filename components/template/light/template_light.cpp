#include "template_switch.h"
#include "esphome/core/log.h"

namespace esphome {
namespace template_ {

static const char *const TAG = "template.light";

TemplateLight::TemplateLight() : turn_on_trigger_(new Trigger<>()), turn_off_trigger_(new Trigger<>()) {}

void TemplateLight::loop() {
  if (!this->f_.has_value())
    return;
  auto s = (*this->f_)();
  if (!s.has_value())
    return;

  this->publish_state(*s);
}
void TemplateLight::write_state(light::LightState *state) {
  bool binary;

  state->current_values_as_binary(&binary);
  if (this->prev_trigger_ != nullptr) {
    this->prev_trigger_->stop_action();
  }

  if (binary) {
    this->prev_trigger_ = this->turn_on_trigger_;
    this->turn_on_trigger_->trigger();
  } else {
    this->prev_trigger_ = this->turn_off_trigger_;
    this->turn_off_trigger_->trigger();
  }

  if (this->optimistic_)
    this->publish_state(state);
}
void TemplateLight::set_optimistic(bool optimistic) { this->optimistic_ = optimistic; }
bool TemplateLight::assumed_state() { return this->assumed_state_; }
void TemplateLight::set_state_lambda(std::function<optional<bool>()> &&f) { this->f_ = f; }
float TemplateLight::get_setup_priority() const { return setup_priority::HARDWARE - 2.0f; }
Trigger<> *TemplateLight::get_turn_on_trigger() const { return this->turn_on_trigger_; }
Trigger<> *TemplateLight::get_turn_off_trigger() const { return this->turn_off_trigger_; }


void TemplateLight::dump_config() {
  ESP_LOGCONFIG(TAG, "Template Light:");
  ESP_LOGCONFIG(TAG, "  Optimistic: %s", YESNO(this->optimistic_));
}

void TemplateLight::set_assumed_state(bool assumed_state) { this->assumed_state_ = assumed_state; }

}  // namespace template_
}  // namespace esphome
