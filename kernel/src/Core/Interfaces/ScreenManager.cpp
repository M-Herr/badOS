#include "Core/Interfaces/ScreenManager.hpp"


ScreenManager screenManager(ScreenManager::Mode::VGA, ScreenManager::MemoryAllocation::Static);

ScreenManager::ScreenManager()
: mode(Mode::VGA), alloc(MemoryAllocation::Static),  vgaDriver(VGADriver())
{
  
}

ScreenManager::ScreenManager(Mode in_mode, MemoryAllocation in_alloc)
: mode(in_mode), alloc(in_alloc), vgaDriver(VGADriver())
{
    
}


void ScreenManager::Initialize()
{
    __attribute__((used, section(".requests")))
    static volatile struct limine_framebuffer_request framebuffer_request = {
        .id = LIMINE_FRAMEBUFFER_REQUEST,
        .revision = 0
    };

    auto framebuffer_response = framebuffer_request.response;

    if(framebuffer_response == nullptr || framebuffer_response->framebuffer_count < 1)
    {
        return;
    }

    struct limine_framebuffer *framebuffer = framebuffer_response->framebuffers[0];

    framebufferDriver.Initialize(framebuffer);
    vgaDriver.Initialize(framebuffer);
}


void ScreenManager::WriteText(const char* text, uint32_t x, uint32_t y)
{
    if(mode == Mode::VGA)
    {
        vgaDriver.SetCursor(x, y);
        size_t index = 0;
        while(text[index] != '\0')
        {
            vgaDriver.WriteChar(text[index]);
            index++;
        }
    }
    else 
    {
        for(size_t i = 0; text[i] != '\0'; ++i) 
        {
            DrawCharacter(text[i], x + i * 8, y); //8x8 
        }
    }
}

void ScreenManager::WriteText(const char* text)
{
    if(mode == Mode::VGA)
    {
        size_t index = 0;
        while(text[index] != '\0')
        {
            if(text[index] == '\n')
            {
                HandleNewline();
            }
            else {
                vgaDriver.WriteChar(text[index]);
            }

            index++;
        }
    }
}

void ScreenManager::HandleNewline()
{
    //Scroll down a line and move the cursor back to column 0
    vgaDriver.GetTextModeCursor()->y++;
    vgaDriver.GetTextModeCursor()->x = 0;
}


void ScreenManager::DrawCharacter(char c, uint32_t x, uint32_t y)
{
    
}


void ScreenManager::Clear()
{
    switch(mode)
    {
        case Mode::VGA:
        {
            vgaDriver.Clear();
            break;
        }
        default:
        break;
    }
}



