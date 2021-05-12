#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "cons.h"
#include "null.h"
#include "constant/numeric.h"
#include "constant/equality.h"
#include <iostream>

namespace ftl{

    //---- methods ----

    /**
    * Construye ua lista
    */
    template<typename... TS>
    struct list : null{};

    template<typename T, typename... TS>
    struct list<T,TS...> : cons<T,typename list<TS...>::type>{};

    template<typename... TS>
    using list_t = typename list<TS...>::type;

    /**
    * Construye una lista numerica. Dado un valor positivo, se generan
    * tantos elementos como se haya indicado. Para cada valor se ejecuta la
    * metafucnion que se le pasa como segundo parametro
    */
    /// TODO: Arreglar
    template<bool stop, typename I, typename N, template<typename> typename F>
    struct build_list_aux : cons<typename F<I>::type, typename build_list_aux<eq_v<add1_t<I>,N>,add1_t<I>,N,F>::type>{};

    template<typename I, typename N, template<typename> typename F>
    struct build_list_aux<true,I,N,F> : null{};

    template<typename N, template<typename> typename F>
    struct build_list : build_list_aux<eq_v<unsigned_long_long_int_constant<0>,N>,unsigned_long_long_int_constant<0>,N,F>{};

    template<typename N, template <typename> typename F>
    using build_list_t = typename build_list<N,F>::type;

    /**
    * Devuelve la lista de enteros entre el rango especificado
    */
    template<bool stop, typename N, typename S, typename P>
    struct range_aux : cons<N,typename range_aux<greater_equal_v<plus_t<N,P>,S>,plus_t<N,P>,S,P>::type>{};

    template<typename N, typename S, typename P>
    struct range_aux<true,N,S,P> : null{};

    template<typename S, typename... TS>
    struct range : range_aux<greater_equal_v<unsigned_long_long_int_constant<0>,S>,unsigned_long_long_int_constant<0>,S,unsigned_long_long_int_constant<1>>{};

    template<typename N, typename S>
    struct range<N,S> : range_aux<greater_equal_v<N,S>,N,S,unsigned_long_long_int_constant<1>>{};

    template<typename N, typename S, typename P>
    struct range<N,S,P> : range_aux<greater_equal_v<N,S>,N,S,P>{};

    template<typename N, typename... NS>
    using range_t = typename range<N,NS...>::type;

    /**
    * Comprueba si un tipo es list
    */
    template<typename T>
    struct is_list : std::false_type{};

    template<>
    struct is_list<null> : std::true_type{};

    template<typename T1, typename T2>
    struct is_list<cons<T1,T2>> : is_list<T2>{};

    template<typename T>
    using is_list_t = typename is_list<T>::type;

    template<typename T>
    static constexpr bool is_list_v = is_list<T>::value;

    /**
    * Devuelve la longitud de una lista
    */
    template<typename T>
    struct length : std::integral_constant<std::size_t,1+length<cdr_t<T>>::value>{};

    template<>
    struct length<null> : std::integral_constant<std::size_t,0>{};

    /**
    * Devuelve el elemento de la lista que ocupa la posicion index
    */
    template<typename T, std::size_t index>
    struct list_ref{
        using type = typename list_ref<cdr_t<T>,index-1>::type;
    };

    template<typename T>
    struct list_ref<T,0>{
        using type = car_t<T>;
    };

    /**
    * Concatena dos listas
    */
    template<typename T1, typename T2>
    struct append{
        using type = cons_t<car_t<T1>,typename append<cdr_t<T1>,T2>::type>;
    };

    template<typename T2>
    struct append<null,T2>{
        using type = T2;
    };

    template<typename T1, typename T2>
    using append_t = typename append<T1,T2>::type;

    /**
    * Invierte el orden de los elementos de una lista
    */
    template<typename T1, typename T2>
    struct reverse_aux{
        using type = typename reverse_aux<cdr_t<T1>,cons_t<car_t<T1>,T2>>::type;
    };

    template<typename T2>
    struct reverse_aux<null,T2>{
        using type = T2;
    };

    template<typename T>
    struct reverse : reverse_aux<T,null>{};

    /**
    * Ejecuta una metafuncion sobre cada elemento de una lista
    * y devuelve otra lista con los resultados
    */
    template<typename... TS>
    struct some_null : std::false_type{};

    template<typename T, typename... TS>
    struct some_null<T,TS...> : std::bool_constant<is_null_v<T> || some_null<TS...>::value>{};

    template<bool stop, template<typename...> typename F, typename... TS>
    struct map_aux{
        using type = cons_t<typename F<car_t<TS>...>::type,typename map_aux<some_null<cdr_t<TS>...>::value,F,cdr_t<TS>...>::type>;
    };

    template<template<typename...> typename F, typename... TS>
    struct map_aux<true,F,TS...>{
        using type = null;
    };

    template<template<typename...> typename F, typename... TS>
    struct map{
        using type = typename map_aux<some_null<TS...>::value,F,TS...>::type;
    };

    template<template<typename...> typename F, typename... TS>
    using map_t = typename map<F,TS...>::type;


    /**
    * Aplana una lista
    */
    template<typename T>
    struct flatten : cons<car_t<T>,typename flatten<cdr_t<T>>::type>{};

    template<typename T, typename R, typename S>
    struct flatten<cons<cons<T,R>,S>> : append<typename flatten<cons<T,R>>::type,typename flatten<S>::type>{};

    template<typename S>
    struct flatten<cons<null,S>> : flatten<S>{};

    template<>
    struct flatten<null> : null{};

    template<typename T>
    using flatten_t = typename flatten<T>::type;

    /**
    * Devuelve una lista con todas las combinaciones posibles
    */
    template<typename T>
    struct permutations_map{
        template<typename TS>
        struct type_f : cons<T,TS>{} ;
    };

    template<typename T>
    struct permutations;

    template<typename T, typename TS>
    struct permutations_first : map<permutations_map<T>::template type_f, typename permutations<TS>::type>{};

    template<typename T>
    struct permutations_first<T,null> : list<list_t<T>>{};

    template<typename TH, typename T, typename TR>
    struct permutations_aux : append<typename permutations_first<T,append_t<TH,TR>>::type, typename permutations_aux<cons_t<T,TH>,car_t<TR>,cdr_t<TR>>::type>{};

    template<typename TH, typename T>
    struct permutations_aux<TH,T,null> : permutations_first<T,TH>{};

    template<typename T>
    struct permutations : permutations_aux<null,car_t<T>,cdr_t<T>>{};

    template<>
    struct permutations<null> : null{};

    template<typename T>
    using permutations_t = typename permutations<T>::type;

    /**
    * Imprime una lista
    */
    template<typename T>
    struct list_print_aux{
        static void exe(){
            std::cout << car_t<T>::value << " ";
            list_print_aux<cdr_t<T>>::exe();
        }
    };

    template<typename T, typename TS, typename RS>
    struct list_print_aux<cons<cons<T,TS>,RS>>{
        static void exe(){
            std::cout << "( ";
            list_print_aux<cons<T,TS>>::exe();
            list_print_aux<RS>::exe();
        }
    };

    template<typename RS>
    struct list_print_aux<cons<null,RS>>{
        static void exe(){
            std::cout << "( ) ";
            list_print_aux<RS>::exe();
        }
    };

    template<>
    struct list_print_aux<null>{
        static void exe(){
            std::cout << ") ";
        }
    };

    template<typename T>
    struct list_print{
        static void exe(){
            std::cout << "'( ";
            list_print_aux<T>::exe();
        }
    };

    template<typename T>
    void list_print_e(){
        list_print<T>::exe();
    }

    /**
    * Comprime dos listas en una que contiene pares de elementos de cada lista
    */
    template<typename T, typename S>
    struct zip : null{};

    template<typename T, typename TS, typename S, typename SS>
    struct zip<cons<T,TS>,cons<S,SS>> : cons<cons_t<T,S>,typename zip<TS,SS>::type>{};

    template<typename T, typename S>
    using zip_t = typename zip<T,S>::type;

    /**
    * Descomprime una lista de pares en dos listas
    */
    template<typename T>
    struct unzip : cons<map_t<car,T>,map_t<cdr,T>>{};

    template<typename T>
    using unzip_t = typename unzip<T>::type;


    //---- shortcuts ----







    template<typename T>
    using length_t = typename length<T>::type;

    template<typename T>
    static constexpr std::size_t length_v = length<T>::value;

    template<typename T, std::size_t index>
    using list_ref_t = typename list_ref<T,index>::type;



    template<typename T>
    using reverse_t = typename reverse<T>::type;




}

#endif // LIST_H_INCLUDED
