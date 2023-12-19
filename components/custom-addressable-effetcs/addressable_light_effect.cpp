#include "addressable_light_effect.h"
#include "esphome/core/log.h"

namespace esphome {
namespace light {


void AddressableTwinkleFoxEffect::apply(AddressableLight &it, const Color &current_color)
{

  uint16_t PRNG16 = 11337; 
  uint32_t clock32 = millis();

  Color bg;
  if( (autoBGColor_) &&
      (gCurrentPalette[0] == gCurrentPalette[1] )) {
    bg = gCurrentPalette[0];
    uint8_t bglight = getAverageLight(bg);
    if( bglight > 64) {
      bg = nscale8_video(bg, 16); // very bright, so scale to 1/16th
    } else if( bglight > 16) {
      bg = nscale8_video(bg, 64); // not that bright, so scale to 1/4th
    } else {
      bg = nscale8_video(bg, 86); // dim, scale to 1/3rd.
    }
  } else {
    bg = gBackgroundColor;
  }

  uint8_t backgroundBrightness = getAverageLight(bg);
  
  for (auto view : it) {
    PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384; // next 'random' number
    uint16_t myclockoffset16= PRNG16; // use that number as clock offset
    PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384; // next 'random' number
    // use that number as clock speed adjustment factor (in 8ths, from 8/8ths to 23/8ths)
    uint8_t myspeedmultiplierQ5_3 =  ((((PRNG16 & 0xFF)>>4) + (PRNG16 & 0x0F)) & 0x0F) + 0x08;
    uint32_t myclock30 = (uint32_t)((clock32 * myspeedmultiplierQ5_3) >> 3) + myclockoffset16;
    uint8_t  myunique8 = PRNG16 >> 8; // get 'salt' value for this pixel

    Color c = AddressableTwinkleFoxEffect::computeOneTwinkle( myclock30, myunique8);

    uint8_t cbright = getAverageLight(c);
    int16_t deltabright = cbright - backgroundBrightness;
    if( deltabright >= 32 || (!bg)) {
      view = c;
    } else if( deltabright > 0 ) {
      pixel = blend( bg, c, deltabright * 8);
    } else { 
      view = bg;
    }
  }
  it.schedule_show();
}

Color AddressableTwinkleFoxEffect::computeOneTwinkle( uint32_t ms, uint8_t salt)
{
  uint16_t ticks = ms >> (8-speed_);
  uint8_t fastcycle8 = ticks;
  uint16_t slowcycle16 = (ticks >> 8) + salt;
  slowcycle16 += sin8( slowcycle16);
  slowcycle16 =  (slowcycle16 * 2053) + 1384;
  uint8_t slowcycle8 = (slowcycle16 & 0xFF) + (slowcycle16 >> 8);
  
  uint8_t bright = 0;
  if( ((slowcycle8 & 0x0E)/2) < density_) {
    bright = attackDecayWave8( fastcycle8);
  }

  uint8_t hue = slowcycle8 - salt;
  Color c;
  if( bright > 0) {
    c = ColorFromPalette( gCurrentPalette, hue, bright, NOBLEND);
    if(_coolLikeIncandescent) {
      AddressableTwinkleFoxEffect::coolLikeIncandescent( c, fastcycle8);
    }
  } else {
    c = Color::Black;
  }
  return c;
}

void AddressableTwinkleFoxEffect::coolLikeIncandescent( Color& c, uint8_t phase)
{
  if( phase < 128) return;

  uint8_t cooling = (phase - 128) >> 4;
  c.g = qsub8( c.g, cooling);
  c.b = qsub8( c.b, cooling * 2);
}


}  // namespace light
}  // namespace esphome