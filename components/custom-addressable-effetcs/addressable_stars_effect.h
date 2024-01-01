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

struct AddressableColorStarsEffectColor {
  uint8_t r, g, b, w;
  uint8_t brightness;
};

class AddressableStarsEffect : public AddressableLightEffect {
 public:
  explicit AddressableStarsEffect(const std::string &name) : AddressableLightEffect(name) {}
  void start() override {
    auto &it = *this->get_addressable_();
    it.all() = Color::BLACK;
    it.schedule_show(); 

    auto r = this->color_effect_.r * this->color_effect_.brightness /100;
    auto g = this->color_effect_.g * this->color_effect_.brightness /100;
    auto b = this->color_effect_.b * this->color_effect_.brightness /100;
    auto w = this->color_effect_.w * this->color_effect_.brightness /100;  
    this->color_ = Color(r, g, b, w);
  }
  
  void apply(AddressableLight &it, const Color &current_color) override {
    for (auto view : it) {     
        Color effect_color = (this->color_ == Color::BLACK ? current_color : this->color_);

        if (view.get_effect_data()==0 && (random_float() * 500 < this->stars_probability_)){
              view.set_effect_data(255);
        } 
        if (view.get_effect_data() > 0) {
            float intensit = -1*pow(view.get_effect_data()/180.1,2);
            view = Color(effect_color.r * exp(intensit),
                         effect_color.g * exp(intensit),
                         effect_color.b * exp(intensit),
                         effect_color.w * exp(intensit));
        } else {
            view = Color::BLACK;
        }
        if (view.get_effect_data()%2 == 1) {
          view.set_effect_data((view.get_effect_data()>2)?view.get_effect_data()-2:2);
        }
        else if (view.get_effect_data() > 0) {
          view.set_effect_data((view.get_effect_data()<=254)?view.get_effect_data()+2:0);
        }
    }
    it.schedule_show();
  }

  void set_stars_probability(float stars_probability) { this->stars_probability_ = stars_probability; }
  void set_color(const AddressableColorStarsEffectColor &color) { this->color_effect_ = color; }

 protected:
  float stars_probability_{0.3};
  AddressableColorStarsEffectColor color_effect_;
  Color color_;

};


}  // namespace light
}  // namespace esphome
