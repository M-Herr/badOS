#pragma once

#include "Types.hpp"
#include "C++/type_traits.hpp"
#include "C++/concepts.hpp"

class Port
{
    public:
    template<blib::integral T>
    static uint8_t read(uint16_t port) ;

    template<blib::integral T>
    static void write(uint16_t port, T value);
    
};
