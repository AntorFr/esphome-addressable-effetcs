#pragma once

#include <utility>
#include <vector>

#include "esphome/core/component.h"

namespace esphome {
namespace light {

typedef uint32_t TProgmemColorPalette16[16];

/// RGB color palette with 16 discrete values
class ColorPalette16 {
public:
    Color entries[16];

    ColorPalette16() {};

    /// Create palette from 16 Color values
    ColorPalette16( const Color& c00,const Color& c01,const Color& c02,const Color& c03,
                    const Color& c04,const Color& c05,const Color& c06,const Color& c07,
                    const Color& c08,const Color& c09,const Color& c10,const Color& c11,
                    const Color& c12,const Color& c13,const Color& c14,const Color& c15 )
    {
        entries[0]=c00; entries[1]=c01; entries[2]=c02; entries[3]=c03;
        entries[4]=c04; entries[5]=c05; entries[6]=c06; entries[7]=c07;
        entries[8]=c08; entries[9]=c09; entries[10]=c10; entries[11]=c11;
        entries[12]=c12; entries[13]=c13; entries[14]=c14; entries[15]=c15;
    };

    /// Copy constructor
    ColorPalette16( const ColorPalette16& rhs)
    {
        memmove8( (void *) &(entries[0]), &(rhs.entries[0]), sizeof( entries));
    }
    /// Create palette from array of Color colors
    ColorPalette16( const Color rhs[16])
    {
        memmove8( (void *) &(entries[0]), &(rhs[0]), sizeof( entries));
    }
    /// Create palette from array of Color colors
    ColorPalette16& operator=( const ColorPalette16& rhs)
    {
        memmove8( (void *) &(entries[0]), &(rhs.entries[0]), sizeof( entries));
        return *this;
    }
    /// Create palette from array of Color colors
    ColorPalette16& operator=( const Color rhs[16])
    {
        memmove8( (void *) &(entries[0]), &(rhs[0]), sizeof( entries));
        return *this;
    }

    /// Create palette from palette stored in PROGMEM
    ColorPalette16( const TProgmemRGBPalette16& rhs)
    {
        for( uint8_t i = 0; i < 16; ++i) {
            entries[i] =  FL_PGM_READ_DWORD_NEAR( rhs + i);
        }
    }
    /// Create palette from palette stored in PROGMEM
    ColorPalette16& operator=( const TProgmemRGBPalette16& rhs)
    {
        for( uint8_t i = 0; i < 16; ++i) {
            entries[i] =  FL_PGM_READ_DWORD_NEAR( rhs + i);
        }
        return *this;
    }

    bool operator==( const ColorPalette16 &rhs) const
    {
        const uint8_t* p = (const uint8_t*)(&(this->entries[0]));
        const uint8_t* q = (const uint8_t*)(&(rhs.entries[0]));
        if( p == q) return true;
        for( uint8_t i = 0; i < (sizeof( entries)); ++i) {
            if( *p != *q) return false;
            ++p;
            ++q;
        }
        return true;
    }
    bool operator!=( const ColorPalette16 &rhs) const
    {
        return !( *this == rhs);
    }

    inline Color& operator[] (uint8_t x) __attribute__((always_inline))
    {
        return entries[x];
    }

    inline const Color& operator[] (uint8_t x) const __attribute__((always_inline))
    {
        return entries[x];
    }

    inline Color& operator[] (int x) __attribute__((always_inline))
    {
        return entries[(uint8_t)x];
    }

    inline const Color& operator[] (int x) const __attribute__((always_inline))
    {
        return entries[(uint8_t)x];
    }

    /// Get the underlying pointer to the CHSV entries making up the palette
    operator Color*()
    {
        return &(entries[0]);
    }


    /// @copydoc CHSVPalette16::CHSVPalette16(const CHSV&)
    ColorPalette16( const Color& c1)
    {
        fill_solid( &(entries[0]), 16, c1);
    }
    /// @copydoc CHSVPalette16::CHSVPalette16(const CHSV&, const CHSV&)
    ColorPalette16( const Color& c1, const Color& c2)
    {
        fill_gradient_RGB( &(entries[0]), 16, c1, c2);
    }
    /// @copydoc CHSVPalette16::CHSVPalette16(const CHSV&, const CHSV&, const CHSV&)
    ColorPalette16( const Color& c1, const Color& c2, const Color& c3)
    {
        fill_gradient_RGB( &(entries[0]), 16, c1, c2, c3);
    }

    ColorPalette16( const Color& c1, const Color& c2, const Color& c3, const Color& c4)
    {
        fill_gradient_RGB( &(entries[0]), 16, c1, c2, c3, c4);
    }

    
    ColorPalette16( TProgmemRGBGradientPalette_bytes progpal )
    {
        *this = progpal;
    }

    ColorPalette16& operator=( TProgmemRGBGradientPalette_bytes progpal )
    {
        TRGBGradientPaletteEntryUnion* progent = (TRGBGradientPaletteEntryUnion*)(progpal);
        TRGBGradientPaletteEntryUnion u;

        // Count entries
        uint16_t count = 0;
        do {
            u.dword = FL_PGM_READ_DWORD_NEAR(progent + count);
            ++count;
        } while ( u.index != 255);

        int8_t lastSlotUsed = -1;

        u.dword = FL_PGM_READ_DWORD_NEAR( progent);
        Color rgbstart( u.r, u.g, u.b);

        int indexstart = 0;
        uint8_t istart8 = 0;
        uint8_t iend8 = 0;
        while( indexstart < 255) {
            ++progent;
            u.dword = FL_PGM_READ_DWORD_NEAR( progent);
            int indexend  = u.index;
            Color rgbend( u.r, u.g, u.b);
            istart8 = indexstart / 16;
            iend8   = indexend   / 16;
            if( count < 16) {
                if( (istart8 <= lastSlotUsed) && (lastSlotUsed < 15)) {
                    istart8 = lastSlotUsed + 1;
                    if( iend8 < istart8) {
                        iend8 = istart8;
                    }
                }
                lastSlotUsed = iend8;
            }
            fill_gradient_RGB( &(entries[0]), istart8, rgbstart, iend8, rgbend);
            indexstart = indexend;
            rgbstart = rgbend;
        }
        return *this;
    }
    ColorPalette16& loadDynamicGradientPalette( TDynamiColorGradientPalette_bytes gpal )
    {
        TRGBGradientPaletteEntryUnion* ent = (TRGBGradientPaletteEntryUnion*)(gpal);
        TRGBGradientPaletteEntryUnion u;

        // Count entries
        uint16_t count = 0;
        do {
            u = *(ent + count);
            ++count;
        } while ( u.index != 255);

        int8_t lastSlotUsed = -1;


        u = *ent;
        Color rgbstart( u.r, u.g, u.b);

        int indexstart = 0;
        uint8_t istart8 = 0;
        uint8_t iend8 = 0;
        while( indexstart < 255) {
            ++ent;
            u = *ent;
            int indexend  = u.index;
            Color rgbend( u.r, u.g, u.b);
            istart8 = indexstart / 16;
            iend8   = indexend   / 16;
            if( count < 16) {
                if( (istart8 <= lastSlotUsed) && (lastSlotUsed < 15)) {
                    istart8 = lastSlotUsed + 1;
                    if( iend8 < istart8) {
                        iend8 = istart8;
                    }
                }
                lastSlotUsed = iend8;
            }
            fill_gradient_RGB( &(entries[0]), istart8, rgbstart, iend8, rgbend);
            indexstart = indexend;
            rgbstart = rgbend;
        }
        return *this;
    }

};

}  // namespace light
}  // namespace esphome
