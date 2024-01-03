#pragma once

#include <utility>
#include <vector>

#include "esphome/core/component.h"
#include "esphome/components/light/light_state.h"
#include "esphome/components/light/addressable_light.h"
#include "esphome/components/light/addressable_light_effect.h"

//#include "FastLED.h"
#include "GradientPalettes.hpp"

namespace esphome {
namespace light {

inline static uint8_t qsub8( uint8_t i, uint8_t j) {
  int t = i - j;
  if( t < 0) t = 0;
  return t;
}

inline static uint8_t getAverageLight(const Color &c){
  uint8_t avg = esp_scale8( c.r, 85) + \
  esp_scale8( c.g, 85) + \
  esp_scale8( c.b, 85);
  return avg;
}

inline static Color nscale8_video(const Color &c, fract8 scale){
  Color new_color;
  uint8_t nonzeroscale = (scale != 0) ? 1 : 0;
  //void nscale8x3_video( uint8_t& r, uint8_t& g, uint8_t& b, fract8 scale)
  new_color.r = (c.r == 0) ? 0 : (((int)c.r * (int)(scale) ) >> 8) + nonzeroscale;
  new_color.g = (c.g == 0) ? 0 : (((int)c.g * (int)(scale) ) >> 8) + nonzeroscale;
  new_color.b = (c.b == 0) ? 0 : (((int)c.b * (int)(scale) ) >> 8) + nonzeroscale;
  new_color.w = (c.w == 0) ? 0 : (((int)c.w * (int)(scale) ) >> 8) + nonzeroscale;
  return new_color;
}

// This function produces a 
// symmetrical up-and-down triangle sawtooth waveform,
// with a faster attack and a slower decay
uint8_t static attackDecayWave8( uint8_t i)
{
  if( i < 86) {
    return i * 3;
  } else {
    i -= 86;
    return 255 - (i + (i/2));
  }
}

class AddressableStarsEffect : public AddressableLightEffect {
 public:
  explicit AddressableStarsEffect(const std::string &name) : AddressableLightEffect(name) {}
  void start() override {
    auto &it = *this->get_addressable_();
    it.all() = Color::BLACK;
    it.schedule_show(); 
  }
  
  void apply(AddressableLight &it, const Color &current_color) override {
    const uint32_t now = millis();
    uint8_t pos_add = 0;
    if (now - this->last_progress_ > this->progress_interval_) {
      const uint32_t pos_add32 = (now - this->last_progress_) / this->progress_interval_;
      pos_add = pos_add32;
      this->last_progress_ += pos_add32 * this->progress_interval_;
    }
    for (auto view : it) {     
        Color effect_color = (this->color_.is_on() ? this->color_ : current_color);

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
<<<<<<< HEAD:components/custom-addressable-effetcs/addressable_light_effect.h
  void set_fps(uint8_t fps) { this->fps_ = fps; }

 protected:
  float stars_probability_{0.05f};
  uint8_t fps_{};

class AddressableTwinkleFoxEffect : public AddressableLightEffect {
 public:
  explicit AddressableTwinkle2Effect(const std::string &name) : AddressableLightEffect(name) {}
  void start() override {
    auto &it = *this->get_addressable_();
    it.all() = Color::BLACK;
  }
  
  void apply(AddressableLight &it, const Color &current_color) override;


 protected:
  Color computeOneTwinkle( uint32_t ms, uint8_t salt);
  void coolLikeIncandescent( Color& c, uint8_t phase);

  uint8_t speed_;
  uint8_t density_;
  CRGB gBackgroundColor;
  bool autoBGColor_;
  bool coolLikeIncandescent_;
  CRGBPalette16 gCurrentPalette;

class AddressableTwinkle2Effect : public AddressableLightEffect {
 public:
  explicit AddressableTwinkle2Effect(const std::string &name) : AddressableLightEffect(name) {}
  void start() override {
    auto &it = *this->get_addressable_();
    it.all() = Color::BLACK;
  }
  
  void apply(AddressableLight &it, const Color &current_color) override {}
  protected:
      void init() override;
      void display() override;

 protected:
  Color makeBrighter( const Color& color, fract8 howMuchBrighter);
  Color makeDarker( const Color& color, fract8 howMuchDarker);
  bool getPixelDirection( uint16_t i);
  void setPixelDirection( uint16_t i, bool dir);
  void brightenOrDarkenEachPixel(fract8 fadeUpAmount, fract8 fadeDownAmount);

  uint8_t _startingBritghtness;
  uint8_t _fadeInSpeed;
  uint8_t _fadeOutSpeed;
  uint8_t _density;
  uint8_t*  _directionFlags;
  CRGBPalette16 gCurrentPalette;
  enum { GETTING_DARKER = 0, GETTING_BRIGHTER = 1 };
=======
  void set_color(const Color &color) { this->color_ = color; }

 protected:
  float stars_probability_{0.3};
  Color color_;
>>>>>>> 4fc7341afe51691c2a337688e3b71bdd37a7d66f:components/custom-addressable-effetcs/addressable_stars_effect.h

};


}  // namespace light
}  // namespace esphome
