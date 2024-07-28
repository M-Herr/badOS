#pragma once

#include <Types.hpp>

class Drawable 
{
    public:
    Drawable();
    ~Drawable();

    virtual void draw() = 0;

    
    private:
};