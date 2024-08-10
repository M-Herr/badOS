#pragma once
#define USE_LIMINE


using uint8_t = unsigned char;
using uint16_t = unsigned short;
using uint32_t = unsigned int;
using uint64_t = unsigned long int;

using size_t = unsigned long long;

using ptrdiff_t = decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr));