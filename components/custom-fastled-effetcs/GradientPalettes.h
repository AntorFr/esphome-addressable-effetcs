#pragma once

// ColorWavesWithPalettes by Mark Kriegsman: https://gist.github.com/kriegsman/8281905786e8b2632aeb

// Gradient Color Palette definitions for 33 different cpt-city color palettes.
//    956 bytes of PROGMEM for all of the palettes together,
//   +618 bytes of PROGMEM for gradient palette code (AVR).
//  1,494 bytes total for all 34 color palettes and associated code.


// A mostly red palette with green accents and white trim.
// "CRGB::Gray" is used as white to keep the brightness more uniform.
const TProgmemRGBPalette16 RedGreenWhite_p FL_PROGMEM =
{  CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
   CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
   CRGB::Red, CRGB::Red, CRGB::Gray, CRGB::Gray,
   CRGB::Green, CRGB::Green, CRGB::Green, CRGB::Green };

// A mostly (dark) green palette with red berries.
#define Holly_Green 0x00580c
#define Holly_Red   0xB00402
const TProgmemRGBPalette16 Holly_p FL_PROGMEM =
{  Holly_Green, Holly_Green, Holly_Green, Holly_Green,
   Holly_Green, Holly_Green, Holly_Green, Holly_Green,
   Holly_Green, Holly_Green, Holly_Green, Holly_Green,
   Holly_Green, Holly_Green, Holly_Green, Holly_Red
};

// A red and white striped palette
// "CRGB::Gray" is used as white to keep the brightness more uniform.
const TProgmemRGBPalette16 RedWhite_p FL_PROGMEM =
{  CRGB::Red,  CRGB::Red,  CRGB::Gray, CRGB::Gray,
   CRGB::Red,  CRGB::Red,  CRGB::Gray, CRGB::Gray,
   CRGB::Red,  CRGB::Red,  CRGB::Gray, CRGB::Gray,
   CRGB::Red,  CRGB::Red,  CRGB::Gray, CRGB::Gray };

// A mostly blue palette with white accents.
// "CRGB::Gray" is used as white to keep the brightness more uniform.
const TProgmemRGBPalette16 BlueWhite_p FL_PROGMEM =
{  CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue,
   CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue,
   CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue,
   CRGB::Blue, CRGB::Gray, CRGB::Gray, CRGB::Gray };

// A pure "fairy light" palette with some brightness variations
#define HALFFAIRY ((CRGB::FairyLight & 0xFEFEFE) / 2)
#define QUARTERFAIRY ((CRGB::FairyLight & 0xFCFCFC) / 4)
const TProgmemRGBPalette16 FairyLight_p FL_PROGMEM =
{  CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight,
   HALFFAIRY,        HALFFAIRY,        CRGB::FairyLight, CRGB::FairyLight,
   QUARTERFAIRY,     QUARTERFAIRY,     CRGB::FairyLight, CRGB::FairyLight,
   CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight };

// A palette of soft snowflakes with the occasional bright one
const TProgmemRGBPalette16 Snow_p FL_PROGMEM =
{  0x304048, 0x304048, 0x304048, 0x304048,
   0x304048, 0x304048, 0x304048, 0x304048,
   0x304048, 0x304048, 0x304048, 0x304048,
   0x304048, 0x304048, 0x304048, 0xE0F0FF };

// A palette reminiscent of large 'old-school' C9-size tree lights
// in the five classic colors: red, orange, green, blue, and white.
#define C9_Red    0xB80400
#define C9_Orange 0x902C02
#define C9_Green  0x046002
#define C9_Blue   0x070758
#define C9_White  0x606820
const TProgmemRGBPalette16 RetroC9_p FL_PROGMEM =
{  C9_Red,    C9_Orange, C9_Red,    C9_Orange,
   C9_Orange, C9_Red,    C9_Orange, C9_Red,
   C9_Green,  C9_Green,  C9_Green,  C9_Green,
   C9_Blue,   C9_Blue,   C9_Blue,
   C9_White
};

// A cold, icy pale blue palette
#define Ice_Blue1 0x0C1040
#define Ice_Blue2 0x182080
#define Ice_Blue3 0x5080C0
const TProgmemRGBPalette16 Ice_p FL_PROGMEM =
{
  Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
  Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
  Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
  Ice_Blue2, Ice_Blue2, Ice_Blue2, Ice_Blue3
};

#define Dark_Grey 0x555555

const TProgmemRGBPalette16 Snow2_p FL_PROGMEM =
{
  CRGB::White, CRGB::White, CRGB::White, CRGB::White,
  Dark_Grey, Dark_Grey, Dark_Grey, Dark_Grey,
  Dark_Grey, Dark_Grey, Dark_Grey, Dark_Grey,
  Dark_Grey, Dark_Grey, Dark_Grey, Dark_Grey
};

const TProgmemRGBPalette16 FireOrange_p FL_PROGMEM =
{
  0xE1A024, 0xE1A024, 0xE1A024, 0xE1A024,
  0xE1A024, 0xE1A024, 0xE1A024, 0xE1A024,
  0xE1A024, 0xE1A024, 0xE1A024, 0xE1A024,
  0xE1A024, 0xE1A024, 0xE1A024, 0xE1A024
};

const TProgmemRGBPalette16 IceColors_p FL_PROGMEM =
{
  CRGB::Black, CRGB::Blue, CRGB::Aqua, CRGB::White
};