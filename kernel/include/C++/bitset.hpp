#pragma once
#include <Types.hpp>


namespace blib
{   
    template<size_t N, typename T = uint8_t>
    class Bitset
    {
        public:
        Bitset();
        ~Bitset();

        static constexpr uint32_t BITS_PER_TYPE = sizeof(T)*8; //number of bits per element of the underlying storage type. T = uint64_t, sizeof(uint64_t) = 8, ->, 8*8,BITS_PER_TYPE = 64

        void Set(size_t pos);
        void Reset(size_t pos);
        bool Test(size_t pos) const;
       

        inline T& operator[](const size_t index) { return data[index]; }

        private:
        static constexpr size_t BITSET_SIZE = (N + BITS_PER_TYPE - 1)/BITS_PER_TYPE;
        T data[BITSET_SIZE];
    };
}


#include "bitset_impl.hpp"


