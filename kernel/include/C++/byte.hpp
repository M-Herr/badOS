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

}