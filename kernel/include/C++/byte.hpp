#pragma once

namespace blib {

enum class byte : unsigned char {};

    // Bitwise OR
    constexpr byte operator|(byte lhs, byte rhs) noexcept {
        return static_cast<byte>(static_cast<unsigned char>(lhs) | static_cast<unsigned char>(rhs));
    }

    // Bitwise AND
    constexpr byte operator&(byte lhs, byte rhs) noexcept {
        return static_cast<byte>(static_cast<unsigned char>(lhs) & static_cast<unsigned char>(rhs));
    }

    // Bitwise XOR
    constexpr byte operator^(byte lhs, byte rhs) noexcept {
        return static_cast<byte>(static_cast<unsigned char>(lhs) ^ static_cast<unsigned char>(rhs));
    }

    // Bitwise NOT
    constexpr byte operator~(byte b) noexcept {
        return static_cast<byte>(~static_cast<unsigned char>(b));
    }

    // Bitwise OR assignment
    constexpr byte& operator|=(byte& lhs, byte rhs) noexcept {
        return lhs = lhs | rhs;
    }

    // Bitwise AND assignment
    constexpr byte& operator&=(byte& lhs, byte rhs) noexcept {
        return lhs = lhs & rhs;
    }

    // Bitwise XOR assignment
    constexpr byte& operator^=(byte& lhs, byte rhs) noexcept {
        return lhs = lhs ^ rhs;
    }

    // Shift left
    constexpr byte operator<<(byte b, int shift) noexcept {
        return static_cast<byte>(static_cast<unsigned char>(b) << shift);
    }

    // Shift right
    constexpr byte operator>>(byte b, int shift) noexcept {
        return static_cast<byte>(static_cast<unsigned char>(b) >> shift);
    }

    // Shift left assignment
    constexpr byte& operator<<=(byte& b, int shift) noexcept {
        return b = b << shift;
    }

    // Shift right assignment
    constexpr byte& operator>>=(byte& b, int shift) noexcept {
        return b = b >> shift;
    }

    // To integer
    template<typename IntegerType>
    constexpr IntegerType to_integer(byte b) noexcept {
        return static_cast<IntegerType>(b);
    }

    template <typename T, typename U, size_t N, size_t Pos>
    T extractBits(U value) {
        static_assert(N > 0 && N <= 64, "Number of bits to extract must be between 1 and 64");
        
        // Create a mask with N bits set to 1
        U mask = (1U << N) - 1;
        
        // Shift the mask to the correct position and apply it to the value
        return static_cast<T>((value >> Pos) & mask);
    }

    // Helper function template to deduce types automatically
    template <size_t N, size_t Pos, typename T = uint32_t, typename U = uint32_t>
    auto extractBitsHelper(U value) {
        return extractBits<T, U, N, Pos>(value);
    }
}