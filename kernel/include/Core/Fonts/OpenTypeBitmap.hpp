#pragma once
#include <Types.hpp>

namespace Core
{
    namespace OpenTypeBitmap
    {
        using int8_t = char;
        struct EBDTHeader
        {
            uint16_t majorVersion;
            uint16_t minorVersion;
        } __attribute__((packed));

        struct SbitLineMetrics
        {
            int8_t ascender;
            int8_t descender;
            uint8_t widthMax;
            int8_t caretSlopeNumerator;
            int8_t caretSlopeDenominator;
            int8_t caretOffset;
            int8_t minOriginSB;
            int8_t minAdvancedSB;
            int8_t maxBeforeBL;
            int8_t minAfterBL;
            int8_t pad1;
            int8_t pad2;
        } __attribute__((packed));

        struct BitmapSize
        {
            uint32_t indexSubtableListOffset;
            uint32_t indexSubtableListSize;
            uint32_t numberOfIndexSubtables;
            uint32_t colorRef;
            SbitLineMetrics hori;
            SbitLineMetrics vert;
            uint16_t startGlyphIndex;
            uint16_t endGlyphIndex; // Corrected typo
            uint8_t ppemX;
            uint8_t ppemY;
            uint8_t bitDepth;
            int8_t flags;
        } __attribute__((packed));

        struct EBLCHeader
        {
            uint16_t majorVersion;
            uint16_t minorVersion;
            uint32_t numSizes;
            const BitmapSize* bitMapSizes; // Change to a pointer
        } __attribute__((packed));

        struct BitmapLocation
        {
            uint32_t offset; // Offset of the bitmap data in EBDT table
            uint16_t length; // Length of the bitmap data
        } __attribute__((packed));

        struct IndexSubtableArray
        {
            uint16_t firstGlyphIndex;
            uint16_t lastGlyphIndex;
            uint32_t additionalOffsetToIndexSubtable; // Offset to an index subtable relative to the start of IndexSubTableArray
        } __attribute__((packed));

        struct IndexSubTableHeader
        {
            uint16_t indexFormat;   // Format of the index data
            uint16_t imageFormat;   // Format of the bitmap data
            uint32_t imageDataOffset; // Offset to the image data from the beginning of the EBDT table
        } __attribute__((packed));

        struct BigGlyphMetrics
        {
            uint8_t height;
            uint8_t width;
            int8_t horiBearingX;
            int8_t horiBearingY;
            uint8_t horiAdvance;
            int8_t vertBearingX;
            int8_t vertBearingY;
            uint8_t vertAdvance;
        } __attribute__((packed));

        struct SmallGlyphMetrics
        {
            uint8_t height;
            uint8_t width;
            int8_t bearingX;
            int8_t bearingY;
            uint8_t advance;
        } __attribute__((packed));
        
        // You may need additional structures or methods to read, interpret, and render the glyph bitmaps
        // based on your specific rendering requirements.
    }
}