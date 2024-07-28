#pragma once
#include "VGAUtils.hpp"
#include "Types.hpp"


struct VGAChar
{
    uint8_t character;
    uint8_t attribute;    
};


class VGATextWriter
{
    public:
    VGATextWriter();
    ~VGATextWriter();

    public:
    
    void clear_row(size_t row);
    void clear_screen();
    void get_color_code();

    void Write(const char* str);

    void WriteDec(int num);

    template<typename T>
    void WriteHex(T num);

    template<typename T>
    void WriteBin(T num);


    void WriteChar(char character);
    private:
    void scroll();

    private:
    static uint32_t row;
    static uint32_t col;
    VGAChar emptyChar;
    VGAChar* vgaChar;
    
};

template<typename T>
void VGATextWriter::WriteHex(T num)
{
    const char* hexChars = "0123456789ABCDEF";
    WriteChar('0');
    WriteChar('x');

    bool leading = true;
    for (int i = sizeof(T)*2 -1; i >= 0; --i)
    {
        uint8_t nibble = (num >> (i * 4)) & 0xF;
        if (nibble != 0 || !leading || i == 0) {
            WriteChar(hexChars[nibble]);
            leading = false;
        }
    }
}

template<typename T>
void VGATextWriter::WriteBin(T num)
{
    const char* binChars = "01";
    WriteChar('0');
    WriteChar('b');

    bool leading = true;
    for (int i = sizeof(T); i >= 0; --i) {
        uint8_t bit = (num >> i) & 0x1;
        if (bit != 0 || !leading || i == 0) {
            WriteChar(binChars[bit]);
            leading = false;
        }
    }
}
