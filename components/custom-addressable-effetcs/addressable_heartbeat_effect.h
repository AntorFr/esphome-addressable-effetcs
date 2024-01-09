#pragma once

#include <utility>
#include <vector>

#include "esphome/core/component.h"
#include "esphome/components/light/light_state.h"
#include "esphome/components/light/addressable_light.h"
#include "esphome/components/light/addressable_light_effect.h"

//#include "FastLED.h"
//#include "GradientPalettes.hpp"

namespace esphome {
namespace light {

class AddressableHeartbeatEffect : public AddressableLightEffect {
 public:
  explicit AddressableHeartbeatEffect(const std::string &name) : AddressableLightEffect(name) {}

  void apply(AddressableLight &it, const Color &current_color) override {
    const uint16_t ms_per_beat = (60000 / this->bpm_);
    const uint16_t second_beat = (ms_per_beat / 3);
    const uint32_t now = millis();
    const uint32_t beat_timer = now - this->last_beat_;

    if (now - this->last_update_ < this->update_interval_)
      return;
    this->last_update_ = now;

    it.all().fade_to_black(15);

    if(beat_timer > ms_per_beat) { // time to reset the beat timer?
      it.all() = current_color;
      this->second_beat_ = true;
      this->lastBeat_ = now;
    }

    if((beat_timer > second_beat) && this->second_beat_) { // time for the second beat?
      it.all() = current_color;
      this->second_beat_ = false;
    }

 
    it.schedule_show();
  }

  void set_update_interval(uint32_t update_interval) { this->update_interval_ = update_interval; }
  void set_bpm(int32_t bpm) { this->bpm_ = bpm; }

 protected:
  uint32_t update_interval_{16};
  uint8_t bpm_{40};

  bool second_beat_;
  uint32_t last_beat_{0};
  uint32_t last_update_{0};



};


}  // namespace light
}  // namespace esphome



          
            

            
