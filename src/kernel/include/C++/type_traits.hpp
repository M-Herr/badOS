#pragma once

namespace blib {
    

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

}