#include "bitset.hpp"


namespace blib
{

    template<size_t N, typename T>
    Bitset<N, T>::Bitset()
    {
        for(size_t i = 0; i < BITSET_SIZE; ++i)
        {
            data[i] = 0;
        }
    }

    template<size_t N, typename T>
    Bitset<N, T>::~Bitset()
    {
        //Nothing to do
    }

    template<size_t N, typename T>
    void Bitset<N, T>::Set(size_t pos)
    {
        data[pos/BITS_PER_TYPE] |= (1 << (pos % BITS_PER_TYPE));
    }

    template<size_t N, typename T>
    void Bitset<N, T>::Reset(size_t pos)
    {
        data[pos/BITS_PER_TYPE] &= ~(1 << (pos % BITS_PER_TYPE));
    }
    
    template<size_t N, typename T>
    bool Bitset<N, T>::Test(size_t pos) const
    {
        return data[pos/BITS_PER_TYPE] & (1 << (pos % BITS_PER_TYPE));
    }

}