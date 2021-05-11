#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#include "../list.h"

namespace ftl{

    //---- type ----

    template<typename T, T... ts>
    struct count : size_constant<0>{};

    template<typename T, T t, T... ts>
    struct count<T,t,ts...> : plus<size_constant<1>,typename count<T,ts...>::type>{};

    template<typename T, T... ts>
    struct array_constant{
        using type = array_constant<T,ts...>;
        using value_type = const T(&)[count<T,ts...>::value];
        static constexpr T value[] = {ts...};
        constexpr operator value_type() const noexcept { return value; }
        constexpr value_type operator()() const noexcept { return value; }
    };

    //---- methods ----

    /**
    * Devuelve la longitud del array
    */
    template<typename T>
    struct array_length{};

    template<typename T, T... ts>
    struct array_length<array_constant<T,ts...>> : size_constant<count<T,ts...>::value>{};

    template<typename T>
    using array_length_t = typename array_length<T>::type;

    template<typename T>
    static constexpr std::size_t array_length_v = array_length<T>::value;

    /**
    * Concatena dos arrays
    */
    template<typename A, typename B>
    struct array_append{};

    template<typename T, T... as, T... bs>
    struct array_append<array_constant<T,as...>,array_constant<T,bs...>> : array_constant<T,as...,bs...>{};

    template<typename A, typename B>
    using array_append_t = typename array_append<A,B>::type;

    template<typename A, typename B>
    static constexpr typename array_append_t<A,B>::value_type array_append_v = array_append<A,B>::value;

    /**
    * Convierte una lista de constantes en un array
    */
    template<typename T>
    struct list_to_array_constant : array_append<array_constant<typename car_t<T>::value_type,car_t<T>::value>, typename list_to_array_constant<cdr_t<T>>::type>{};

    template<typename S>
    struct list_to_array_constant<cons<S,null>> : array_constant<typename S::value_type,S::value>{};

    template<typename T>
    using list_to_array_constant_t = typename list_to_array_constant<T>::type;

    template<typename T>
    static constexpr typename list_to_array_constant_t<T>::value_type list_to_array_constant_v = list_to_array_constant<T>::value;



}


#endif // ARRAY_H_INCLUDED
