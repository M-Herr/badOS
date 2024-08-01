#pragma once
#include "C/cmemory.hpp"

namespace blib {
    
    
    template<typename T, T v>
    struct integral_constant 
    {
        static constexpr T value = v;
        using value_type = T;
        using type = integral_constant;
        constexpr operator value_type() const noexcept { return value;}
    };

    using true_type = integral_constant<bool, true>;
    using false_type = integral_constant<bool, false>;

    template<bool B, typename T, typename F>
    struct conditional {using type = T;};

    template<typename T, typename F>
    struct conditional<false, T, F> { using type = F;};

    template<typename...>
    using void_t = void;


    template<typename T, bool = __is_enum(T)>
    struct underlying_type_impl;

    //Specialize for enums
    template<typename T>
    struct underlying_type_impl<T, true>
    {
        using type = __underlying_type(T);
    };


    template<typename T>
    struct underlying_type_impl<T, false>
    {
        using type = T;
    };


    template<typename T>
    struct underlying_type 
    {
        using type  = typename underlying_type_impl<T>::type;
    };

    template<typename T>
    using underlying_type_t = typename underlying_type<T>::type;

    template<typename T>
    struct is_enum {
        static constexpr bool value = __is_enum(T);
    };

    template<bool B, typename T = void>
    struct enable_if {};

    template<typename T>
    struct enable_if<true, T> {
        using type = T;
    };

    template<bool B, typename T = void>
    using enable_if_t = typename enable_if<B, T>::type;


    template<typename T>
    T&& declval() noexcept;

    template<typename T, typename... Args>
    struct is_trivially_constructible_impl : false_type {};

    template <typename T, typename... Args>
    struct is_trivially_constructible_impl<T, void_t<decltype(T(declval<Args>()...))>,  Args...>
            : integral_constant<bool, __is_trivially_constructible(T, Args...)> {};

    template<typename T, typename... Args>
    inline constexpr bool is_trivially_constructible_v = is_trivially_constructible_impl<T, Args...>::value;

    template<typename T, typename... Args>
    concept is_trivially_constructible = is_trivially_constructible_v<T, Args...>;

    template<typename T, typename=void>
    struct is_trivially_copyable_impl : false_type {};

    template<typename T>
    struct is_trivially_copyable_impl<T, void_t<decltype(__is_trivially_copyable(T))>>
    : integral_constant<bool, __is_trivially_copyable(T)> {};

    template<typename T, typename... Args>
    inline constexpr bool is_trivially_copyable_v = is_trivially_copyable_impl<T, Args...>::value;

    template<typename T, typename... Args>
    concept is_trivially_copyable = is_trivially_copyable_v<T, Args...>;


    template<class To, class From>
    enable_if_t<
            sizeof(To) == sizeof(From) 
            && is_trivially_copyable_v<From> 
            && is_trivially_copyable_v<To>,
        To>
    // constexpr support needs compiler magic
    bit_cast(const From& src) noexcept
    {
        To dst;
        memcpy(&dst, &src, sizeof(To));
        return dst;
    }

    // Base template for index_sequence
    template<size_t... Indices>
    struct index_sequence {
        using type = index_sequence;
        static constexpr size_t size() noexcept { return sizeof...(Indices); }
    };

    // Helper template for generating index_sequence
    template<size_t N, size_t... Indices>
    struct make_index_sequence_helper : make_index_sequence_helper<N - 1, N - 1, Indices...> {};

    // Specialization for base case
    template<size_t... Indices>
    struct make_index_sequence_helper<0, Indices...> {
        using type = index_sequence<Indices...>;
    };

    // Alias template for easier usage
    template<size_t N>
    using make_index_sequence = typename make_index_sequence_helper<N>::type;
}