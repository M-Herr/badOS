#include "Core/Fonts/FontParser.hpp"

namespace Core {
namespace Fonts {

FontParser::FontParser()
{

}

FontParser::~FontParser()
{

}

void FontParser::ReadHeaders(const uint8_t* font_data, OpenTypeBitmap::EBDTHeader & ebdtHeader, OpenTypeBitmap::EBLCHeader &eblcHeader)
{
    namespace OTB = OpenTypeBitmap;

    const uint8_t* ptr = font_data;

    // Read EBDTHeader
    ebdtHeader = *reinterpret_cast<const OTB::EBDTHeader*>(ptr);
    ptr += sizeof(OTB::EBDTHeader);

    eblcHeader = *reinterpret_cast<const OTB::EBLCHeader*>(ptr);
    ptr += sizeof(OTB::EBLCHeader);


    eblcHeader.bitMapSizes = reinterpret_cast<const OTB::BitmapSize*>(ptr);    

}


void FontParser::readIndexSubtableArray(const uint8_t* fontData, const OpenTypeBitmap::BitmapSize &bitmapSize, OpenTypeBitmap::IndexSubtableArray* indexSubtableArray, uint32_t maxSubtables)
{
    const uint8_t* ptr = fontData + bitmapSize.indexSubtableListOffset;

    for(uint32_t i = 0; i < bitmapSize.numberOfIndexSubtables && i < maxSubtables; ++i)
    {
        indexSubtableArray[i] = *reinterpret_cast<const OpenTypeBitmap::IndexSubtableArray*>(ptr);
        ptr += sizeof(OpenTypeBitmap::IndexSubtableArray);
    }
}


OpenTypeBitmap::IndexSubTableHeader FontParser::readIndexSubTableHeader(const uint8_t* fontData, uint32_t offset)
{
    const uint8_t* ptr = fontData + offset;
    return *reinterpret_cast<const OpenTypeBitmap::IndexSubTableHeader*>(ptr);
}

void FontParser::LoadFont()
{
    fontData = _binary_gohufont_otb_start;
    
    ReadHeaders(fontData, ebdtHeader, eblcHeader);
    
}


}
}