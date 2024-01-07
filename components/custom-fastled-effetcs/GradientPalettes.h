#pragma once

// ColorWavesWithPalettes by Mark Kriegsman: https://gist.github.com/kriegsman/8281905786e8b2632aeb

// Gradient Color Palette definitions for 33 different cpt-city color palettes.
//    956 bytes of PROGMEM for all of the palettes together,
//   +618 bytes of PROGMEM for gradient palette code (AVR).
//  1,494 bytes total for all 34 color palettes and associated code.


// A mostly red palette with green accents and white trim.
// "Color::Gray" is used as white to keep the brightness more uniform.
const TProgmemColorPalette16 RedGreenWhite_p PROGMEM =
{  Color::Red, Color::Red, Color::Red, Color::Red,
   Color::Red, Color::Red, Color::Red, Color::Red,
   Color::Red, Color::Red, Color::Gray, Color::Gray,
   Color::Green, Color::Green, Color::Green, Color::Green };

// A mostly (dark) green palette with red berries.
const TProgmemColorPalette16 Holly_p PROGMEM =
{  Color::HollyGreen, Color::HollyGreen, Color::HollyGreen, Color::HollyGreen,
   Color::HollyGreen, Color::HollyGreen, Color::HollyGreen, Color::HollyGreen,
   Color::HollyGreen, Color::HollyGreen, Color::HollyGreen, Color::HollyGreen,
   Color::HollyGreen, Color::HollyGreen, Color::HollyGreen, Color::HollyRed
};

// A red and white striped palette
// "Color::Gray" is used as white to keep the brightness more uniform.
const TProgmemColorPalette16 RedWhite_p PROGMEM =
{  Color::Red,  Color::Red,  Color::Gray, Color::Gray,
   Color::Red,  Color::Red,  Color::Gray, Color::Gray,
   Color::Red,  Color::Red,  Color::Gray, Color::Gray,
   Color::Red,  Color::Red,  Color::Gray, Color::Gray };

// A mostly blue palette with white accents.
// "Color::Gray" is used as white to keep the brightness more uniform.
const TProgmemColorPalette16 BlueWhite_p PROGMEM =
{  Color::Blue, Color::Blue, Color::Blue, Color::Blue,
   Color::Blue, Color::Blue, Color::Blue, Color::Blue,
   Color::Blue, Color::Blue, Color::Blue, Color::Blue,
   Color::Blue, Color::Gray, Color::Gray, Color::Gray };

// A pure "fairy light" palette with some brightness variations
const TProgmemColorPalette16 FairyLight_p PROGMEM =
{  Color::FairyLight, Color::FairyLight, Color::FairyLight, Color::FairyLight,
   Color::HalfFairyLight,        Color::HalfFairyLight,        Color::FairyLight, Color::FairyLight,
   Color::QuarterFairyLight,     Color::QuarterFairyLight,     Color::FairyLight, Color::FairyLight,
   Color::FairyLight, Color::FairyLight, Color::FairyLight, Color::FairyLight };

// A palette of soft snowflakes with the occasional bright one
const TProgmemColorPalette16 Snow_p PROGMEM =
{  Color::DarkSnow, Color::DarkSnow, Color::DarkSnow, Color::DarkSnow,
   Color::DarkSnow, Color::DarkSnow, Color::DarkSnow, Color::DarkSnow,
   Color::DarkSnow, Color::DarkSnow, Color::DarkSnow, Color::DarkSnow,
   Color::DarkSnow, Color::DarkSnow, Color::DarkSnow, Color::Snow };

// A palette reminiscent of large 'old-school' C9-size tree lights
// in the five classic colors: red, orange, green, blue, and white.
const TProgmemColorPalette16 RetroC9_p PROGMEM =
{  Color::C9Red,    Color::C9Orange, Color::C9Red,    Color::C9Orange,
   Color::C9Orange, Color::C9Red,    Color::C9Orange, Color::C9Red,
   Color::C9Green,  Color::C9Green,  Color::C9Green,  Color::C9Green,
   Color::C9Blue,   Color::C9Blue,   Color::C9Blue,
   Color::C9White
};

// A cold, icy pale blue palette
#define Ice_Blue1 0x0C1040
#define Ice_Blue2 0x182080
#define Ice_Blue3 0x5080C0
const TProgmemColorPalette16 Ice_p PROGMEM =
{
  Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
  Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
  Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
  Ice_Blue2, Ice_Blue2, Ice_Blue2, Ice_Blue3
};

#define Dark_Grey 0x555555

const TProgmemColorPalette16 Snow2_p PROGMEM =
{
  Color::White, Color::White, Color::White, Color::White,
  Dark_Grey, Dark_Grey, Dark_Grey, Dark_Grey,
  Dark_Grey, Dark_Grey, Dark_Grey, Dark_Grey,
  Dark_Grey, Dark_Grey, Dark_Grey, Dark_Grey
};

const TProgmemColorPalette16 FireOrange_p PROGMEM =
{
  0xE1A024, 0xE1A024, 0xE1A024, 0xE1A024,
  0xE1A024, 0xE1A024, 0xE1A024, 0xE1A024,
  0xE1A024, 0xE1A024, 0xE1A024, 0xE1A024,
  0xE1A024, 0xE1A024, 0xE1A024, 0xE1A024
};

const TProgmemColorPalette16 IceColors_p PROGMEM =
{
  Color::Black, Color::Blue, Color::Aqua, Color::White
};