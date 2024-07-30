#pragma once

#include <Types.hpp>

class Drawable 
{
    public:
    Drawable() = default;
    virtual ~Drawable() = default;

    virtual void draw() = 0;

    
    private:
};