#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#include "../list.h"

namespace ftl{

    //---- type ----

    // Necesita al menos un elemento para saber value_type
    template<typename T, typename... TS>
    struct array_constant{
        using type = array_constant<T,TS...>;
        using value_type = const typename T::value_type(&)[length_v<list_t<T,TS...>>];
        static constexpr typename T::value_type value[] = {T::value,TS::value...};
        constexpr operator value_type() const noexcept { return value; }
        constexpr value_type operator()() const noexcept { return value; }
    };

    //---- methods ----

    /**
    * Devuelve la longitud del array
    */
    template<typename T>
    struct array_length{};

    template<typename T, typename... TS>
    struct array_length<array_constant<T,TS...>> : length<list_t<T,TS...>>{};

    template<typename T>
    using array_length_t = typename array_length<T>::type;

    template<typename T>
    static constexpr std::size_t array_length_v = array_length<T>::value;

    /**
    * Concatena dos arrays
    */
    template<typename A, typename B>
    struct array_append{};

    template<typename T, typename... TS, typename S, typename... SS>
    struct array_append<array_constant<T,TS...>,array_constant<S,SS...>> : array_constant<T,TS...,S,SS...>{};

    template<typename A, typename B>
    using array_append_t = typename array_append<A,B>::type;

    template<typename A, typename B>
    static constexpr typename array_append_t<A,B>::value_type array_append_v = array_append<A,B>::value;

    /**
    * Convierte una lista de constantes en un array
    */
    template<typename T>
    struct list_to_array_constant : array_append<array_constant<car_t<T>>, typename list_to_array_constant<cdr_t<T>>::type>{};

    template<typename S>
    struct list_to_array_constant<cons<S,null>> : array_constant<S>{};

    template<typename T>
    using list_to_array_constant_t = typename list_to_array_constant<T>::type;

    template<typename T>
    static constexpr typename list_to_array_constant_t<T>::value_type list_to_array_constant_v = list_to_array_constant<T>::value;



}


#endif // ARRAY_H_INCLUDED
