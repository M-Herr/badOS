#include "Hardware/VGA/VGA.hpp"
#include "Hardware/VGA/VGAUtils.hpp"
#include "Types.hpp"


uint32_t VGATextWriter::row = 0;
uint32_t VGATextWriter::col = 0;


VGATextWriter::VGATextWriter()
{
    emptyChar = VGAChar {.character = ' ', .attribute = static_cast<blib::underlying_type_t<VGAColors>>(VGAColors::Black) };
    
    vgaChar = reinterpret_cast<VGAChar*>(VGAProperties::start_address);
}

VGATextWriter::~VGATextWriter()
{

}

void VGATextWriter::WriteChar(char character)
{   
    if(vgaChar == nullptr)
    {
        vgaChar = reinterpret_cast<VGAChar*>(VGAProperties::start_address);
    }

    if(col >= VGAProperties::width || character == '\n')
    {
        row++;
        col = 0;
    }
    else 
    {   
        vgaChar[col + VGAProperties::width * row].character = character;
        vgaChar[col + VGAProperties::width * row].attribute = static_cast<blib::underlying_type_t<VGAColors>>(VGAColors::Green | VGAColors::Black << 4);
        col++;
    }
}

void VGATextWriter::Write(const char* str)
{
    if(vgaChar == nullptr)
    {
        vgaChar = reinterpret_cast<VGAChar*>(VGAProperties::start_address);
    }

    size_t index = 0;
    while(str[index] != 0)
    {   
        char character = str[index];
        WriteChar(character);
        index++;    
    }
        
    if(row >= VGAProperties::height)
    {
        scroll();
        row = row -1;
        col = 0;
    }
}

   
void VGATextWriter::WriteDec(int num) {
    if (num == 0) {
        WriteChar('0');
        return;
    }

    if (num < 0) {
        WriteChar('-');
        num = -num;
    }

    char buffer[16];
    int i = 0;

    while (num > 0) {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }

    for (int j = i - 1; j >= 0; --j) {
        WriteChar(buffer[j]);
    }
}

void VGATextWriter::clear_screen()
{
    if(vgaChar == nullptr)
    {
        vgaChar = reinterpret_cast<VGAChar*>(VGAProperties::start_address);
    }

    for(size_t i = 0; i < VGAProperties::height; ++i)
    {
       clear_row(i);
    }

    row = col = 0;
}



void VGATextWriter::clear_row(size_t row_to_clear)
{      
    for(size_t i = 0; i < VGAProperties::width; ++i)
    {
       vgaChar[ i + VGAProperties::width * row_to_clear] = emptyChar;
    }

}

void VGATextWriter::scroll()
{
    for(int r = 0; r < VGAProperties::height - 1; ++r)
    {
        for(int c = 0; c < VGAProperties::width; ++c)
        {
            //Copy contents of cell to one above
            vgaChar[r * VGAProperties::width + c] = vgaChar[(r + 1)*VGAProperties::width + c];
            //clear_row(r+1);
        }
    }

}

