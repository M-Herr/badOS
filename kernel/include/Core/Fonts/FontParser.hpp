#pragma once
#include <Types.hpp>
#include "OpenTypeBitmap.hpp"

namespace Core {
namespace Fonts {

extern "C" {
extern uint8_t _binary_gohufont_otb_start[];
extern uint8_t _binary_gohufont_otb_size[];
extern uint8_t _binary_gohufont_otb_end[];
}

class FontParser
{
    public:
    FontParser();
    ~FontParser();

    void ReadHeaders(const uint8_t* font_data, OpenTypeBitmap::EBDTHeader & ebdtHeader, OpenTypeBitmap::EBLCHeader &eblcHeader);

    void readIndexSubtableArray(const uint8_t* fontData, const OpenTypeBitmap::BitmapSize &bitmapSize, OpenTypeBitmap::IndexSubtableArray* indexSubtableArray, uint32_t maxSubtables);

    OpenTypeBitmap::IndexSubTableHeader readIndexSubTableHeader(const uint8_t* fontData, uint32_t offset);

    void LoadFont();
    OpenTypeBitmap::EBDTHeader ebdtHeader;
    OpenTypeBitmap::EBLCHeader eblcHeader;
    uint8_t* fontData;
    
    private:
   
};


}
}