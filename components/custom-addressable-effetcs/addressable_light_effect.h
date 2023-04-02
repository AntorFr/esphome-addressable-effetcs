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

class AddressableStarsEffect : public AddressableLightEffect {
 public:
  explicit AddressableStarsEffect(const std::string &name) : AddressableLightEffect(name) {}
  void start() override {
    auto &it = *this->get_addressable_();
    it.all() = Color::BLACK;
  }
  
  void apply(AddressableLight &it, const Color &current_color) override {
    for (auto view : it) {
        if (view.get_effect_data()==0 && random16(60*this->stars_probability_)==0){
             view.set_effect_data(255);
        } 
        if (view.get_effect_data() > 0) {
            float intensit = -1*pow(view.get_effect_data()/180.1,2);
            view = Color(current_color * exp(intensit))
        } else {
            view = CRGB::Black;
        }
        if (view.get_effect_data()%2 == 1) {view.set_effect_data(view.get_effect_data()>2)?view.get_effect_data()-2:2;}
        else if (view.get_effect_data() > 0) {view.set_effect_data(view.get_effect_data()<=254)?view.get_effect_data()+2:0;}
    }
    it.schedule_show();
  }

  void set_stars_probability(uint8_t stars_probability) { this->stars_probability_ = stars_probability; }

 protected:
  uint8_t stars_probability_{100};


};


}  // namespace light
}  // namespace esphome
