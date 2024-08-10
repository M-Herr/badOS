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
    
    template<bool B, typename T, typename F>
    using conditional_t = typename conditional<B, T, F>::type;

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

    /*
    /
    / IS_INTEGRAL
    /
    */

    template<typename T>
    struct is_integral {
        static constexpr bool value = false;
    };

    template<>
    struct is_integral<bool> {
        static constexpr bool value = true;
    };

    template<>
    struct is_integral<char> {
        static constexpr bool value = true;
    };

    template<>
    struct is_integral<signed char> {
        static constexpr bool value = true;
    };

    template<>
    struct is_integral<unsigned char> {
        static constexpr bool value = true;
    };

    template<>
    struct is_integral<short> {
        static constexpr bool value = true;
    };

    template<>
    struct is_integral<unsigned short> {
        static constexpr bool value = true;
    };

    template<>
    struct is_integral<int> {
        static constexpr bool value = true;
    };

    template<>
    struct is_integral<unsigned int> {
        static constexpr bool value = true;
    };

    template<>
    struct is_integral<long> {
        static constexpr bool value = true;
    };

    template<>
    struct is_integral<unsigned long> {
        static constexpr bool value = true;
    };

    template<>
    struct is_integral<long long> {
        static constexpr bool value = true;
    };

    template<>
    struct is_integral<unsigned long long> {
        static constexpr bool value = true;
    };

    // Helper variable template for convenience
    template<typename T>
    constexpr bool is_integral_v = is_integral<T>::value;

    /*
    /
    / IS_SAME
    /
    */

   template<typename T, typename U>
   struct is_same {
    static constexpr bool value = false;
   };

   template<typename T>
   struct is_same<T, T> {
    static constexpr bool value = true;
   };

   template<typename T, typename U>
   constexpr bool is_same_v = is_same<T, U>::value;

   /*
    /
    / REMOVE Reference
    /
    */

    template<typename T>
    struct remove_reference
    {
        using type = T;
    };

    template<typename T>
    struct remove_reference<T&>
    {
        using type = T;
    };

    template<typename T>
    struct remove_reference<T&&>
    {
        using type = T;
    };

    template<typename T>
    using remove_reference_t = typename remove_reference<T>::type;

    /*
    /
    / REMOVE CV
    /
    */

    template<typename T>
    struct remove_cv
    {
        using type = T;
    };

    template<typename T>
    struct remove_cv<const T>
    {
        using type = T;
    };

    template<typename T>
    struct remove_cv<volatile T>
    {
        using type = T;
    };

    template<typename T>
    struct remove_cv<const volatile T>
    {
        using type = T;
    };

    template<typename T>
    using remove_cv_t = typename remove_cv<T>::type;

    /*
    /
    / IS ARRAY
    /
    */
    template<typename T>
    struct is_array
    {
        static constexpr bool value = false;
    };

    template<typename T>
    struct is_array<T[]>
    {
        static constexpr bool value = true;
    };

    template<typename T, size_t N>
    struct is_array<T[N]>
    {
        static constexpr bool value = true;
    };

     /*
    /
    / IS FUNCTION
    /
    */
    
    template<typename T>
    struct is_function
    {
        static constexpr bool value = false;
    };

    template<typename Ret, typename... Args>
    struct is_function<Ret(Args...)> {
        static constexpr bool value = true;
    };

    template<typename Ret, typename... Args>
    struct is_function<Ret(Args...) const> {
        static constexpr bool value = true;
    };

    template<typename Ret, typename... Args>
    struct is_function<Ret(Args...) volatile> {
        static constexpr bool value = true;
    };

    template<typename Ret, typename... Args>
    struct is_function<Ret(Args...) const volatile> {
        static constexpr bool value = true;
    };
     /*
    /
    / REMOVE CVREF
    /
    */

    template<typename T>
    struct remove_cvref
    {
        using type = typename remove_cv<T>::type; 
    };

    template<typename T>
    struct remove_cvref<T&>
    {
        using type = typename remove_cv<T>::type; 
    };

    template<typename T>
    struct remove_cvref<T&&>
    {
        using type = typename remove_cv<T>::type;
    };

    template<typename T>
    using remove_cvref_t = typename remove_cvref<T>::type;
    
    /*
    /
    / IS CONST
    /
    */

    template<typename>
    struct is_const;

    template<typename>
    struct is_const : public false_type { };

    template<typename T>
    struct is_const<T const> : public true_type{ };
    

    /*
    /
    / Add Pointer
    /
    */

    template<typename T, typename = void>
    struct add_pointer_helper
    {
        using type = T;
    };

    template<typename T>
    struct add_pointer_helper<T, void_t<T*>>
    {
        using type = T*;
    };

    template<typename T>
    struct add_pointer
    : public add_pointer_helper<T>
    {

    };

    template<typename T>
    struct add_pointer<T&>
    {
        using type = T*;
    };

    template<typename T>
    struct add_pointer<T&&>
    {
        using type = T*;
    };

    /*
    /
    / REMOVE EXTENT
    /
    */
    template<typename T>
    struct remove_extent 
    {
        using type = T;
    };

    template<typename T>
    struct remove_extent<T[]> 
    {
        using type = T;
    };

    template<typename T, size_t N>
    struct remove_extent<T[N]> 
    {
        using type = T;
    };

    /*
    /
    / DECAY
    /
    */

    template<typename T>
    struct decay {
        private:
            using U = remove_reference_t<T>;
        public:
            using type = typename conditional<
            is_array<U>::value,
            typename remove_extent<U>::type*,
            typename conditional<
                is_function<U>::value,
                U*,
                remove_cv_t<U>
            >::type
        >::type;
    };

    template<typename T>
    using decay_t = typename decay<T>::type;
    /*
    /
    / COMMON_TYPE
    /
    */
    // Helper structure to indicate a successful type check
    template<typename T>
    struct success_type
    { 
       using type = T;
    };

    struct failure_type { };

    // Conditional type alias template
    template<typename T, typename U>
    using cond_t = decltype(true ? declval<T>() : declval<U>());
    
    //if sizeof...(T) is zero, no member type
    template<typename... _Tp>
    struct common_type;

    struct do_common_type_impl
    {
        template<typename T, typename U>
        static success_type<decay_t<cond_t<T, U>>>
        MagicTest(int);

        template<typename T, typename U>
        static success_type<remove_cvref_t<cond_t<const T&, const U&>>>
        MagicTest2(int);

        template<typename, typename>
        static failure_type MagicTest2(...);

        template<typename T, typename U>
        static decltype(MagicTest2<T, U>(0))
        MagicTest(...);
    };

    template<>
    struct common_type<>
    { };
    
    template<typename T, typename U>
    struct common_type<T, U, decltype(void(do_common_type_impl::MagicTest<T, U>(0)))> {
        using type = typename decltype(do_common_type_impl::MagicTest<T, U>(0))::type;
    };

    template<typename T>
    struct common_type<T>
    : public common_type<T, T>
     { };

    template<typename T, typename U,
        typename DT = decay_t<T>, typename DU = decay_t<U>>
    struct common_type_impl
    {
        using type = common_type<DT, DU>;
    };

    template<typename T, typename U>
    struct common_type_impl<T, U, T, U>
    : private do_common_type_impl
    {
        using type = decltype(MagicTest<T, U>(0));
    };

    template<typename T, typename U>
    struct common_type<T, U>
    : public common_type_impl<T, U>::type
    { };
    
    template<typename...>
    struct common_type_pack 
    { };

    template<typename, typename, typename = void>
    struct common_type_fold;

    template<typename T, typename U, typename... R>
    struct common_type<T, U, R...>
    : public common_type_fold<common_type<T, U>,
        common_type_pack<R...>>
    { };

    template<typename CT, typename... R>
    struct common_type_fold<CT, common_type_pack<R...>,
        void_t<typename CT::type>>
        : public common_type<typename CT::type, R...>
        { };

    template<typename CT, typename R>
    struct common_type_fold<CT, R, void>
    { };

    template<typename... _Tp>
    using common_type_t = typename common_type<_Tp...>::type;

    template<typename T, typename U, typename... Rest>
    using common_type_variadic_t = typename common_type<T, U, Rest...>::type;
}