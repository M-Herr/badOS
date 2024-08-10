#include "C++/init.hpp"

extern "C" {
    typedef void (*constructor_t)(void);
    extern constructor_t __init_array_start;
    extern constructor_t __init_array_end;
}

void _init() {
    for (constructor_t* ctor = &__init_array_start; ctor != &__init_array_end; ++ctor) {
        (*ctor)();
    }
}

void _fini() {
    // Finalization code if needed
}
