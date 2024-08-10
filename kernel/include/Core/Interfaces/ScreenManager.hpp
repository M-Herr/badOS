#pragma once
#include <Types.hpp>
#include "Core/Interfaces/Screenbuffer.hpp"
#include "Core/Drivers/VGADriver.hpp"
#include "Core/Drivers/FramebufferDriver.hpp"

#include "../bootloader/limine/limine.h"

class ScreenManager
{
    public:

    enum class Mode {
        VGA,
        Framebuffer
    };

    enum class MemoryAllocation
    {
        Static,
        Dynamic
    };

    ScreenManager();
    ScreenManager(Mode in_mode, MemoryAllocation in_alloc);

    void Initialize();

    inline void SetMode(Mode in_mode) { mode = in_mode;}
    inline void SetAlloc(MemoryAllocation in_alloc) { alloc = in_alloc;}
    
    inline Mode GetMode() const {return mode;}
    inline MemoryAllocation GetAlloc() const { return alloc;}

    void WriteText(const char* text, uint32_t x, uint32_t y);
    void WriteText(const char* text);
    void Clear();

    private:
    Mode mode;
    MemoryAllocation alloc;

    VGADriver vgaDriver;
    FramebufferDriver framebufferDriver;

    private:
    void HandleNewline();
    void DrawCharacter(char c, uint32_t x, uint32_t y);

};

extern ScreenManager screenManager;