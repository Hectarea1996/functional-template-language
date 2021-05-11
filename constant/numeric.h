#ifndef INT_CONSTANT_H_INCLUDED
#define INT_CONSTANT_H_INCLUDED


namespace ftl{

    //---- type ----

    /// Types from https://en.cppreference.com/w/cpp/language/types

    template<short int n>
    using short_int_constant = std::integral_constant<short int,n>;

    template<unsigned short int n>
    using unsigned_short_int_constant = std::integral_constant<unsigned short int,n>;

    template<int n>
    using int_constant = std::integral_constant<int,n>;

    template<std::size_t n>
    using size_constant = std::integral_constant<std::size_t,n>;

    template<unsigned int n>
    using unsigned_int_constant = std::integral_constant<unsigned int,n>;

    template<long int n>
    using long_int_constant = std::integral_constant<long int,n>;

    template<unsigned long int n>
    using unsigned_long_int_constant = std::integral_constant<unsigned long int,n>;

    template<long long int n>
    using long_long_int_constant = std::integral_constant<long long int,n>;

    template<unsigned long long int n>
    using unsigned_long_long_int_constant = std::integral_constant<unsigned long long int,n>;

    //---- methods ----

    /**
    * Comprueba que un numero sea 0
    */
    template<typename N>
    struct is_zero : bool_constant<N::value==0>{};

    /**
    * Suma una cantidad variable de enteros
    */
    template<typename... NS>
    struct plus : std::integral_constant<decltype(0),0>{};

    template<typename N, typename... NS>
    struct plus<N,NS...> : std::integral_constant<decltype(N::value+plus<NS...>::value),N::value+plus<NS...>::value>{};

    /**
    * 1-parametro: Devuelve el entero opuesto
    * en otro caso: Le resta al primer argumento el resto de argumentos
    */
    template<typename N, typename... NS>
    struct minus : std::integral_constant<decltype(-N::value),-N::value>{};

    template<typename N, typename M, typename... NS>
    struct minus<N,M,NS...> : std::integral_constant<decltype(N::value-M::value),N::value-M::value>{};

    template<typename N, typename M, typename O, typename... NS>
    struct minus<N,M,O,NS...> : minus<std::integral_constant<decltype(N::value-M::value),N::value-M::value>,O,NS...>{};

    /**
    * Realiza el producto de una cantidad variable de enteros
    */
    template<typename... NS>
    struct mult : std::integral_constant<decltype(1),1>{};

    template<typename N, typename... NS>
    struct mult<N,NS...> : std::integral_constant<decltype(N::value*mult<NS...>::value),N::value*mult<NS...>::value>{};

    /**
    * 1-parametro: Devuelve el entero inverso
    * en otro caso: Divide el primer argumento entre el resto de argumentos
    */
    template<typename N, typename... NS>
    struct div : std::integral_constant<decltype(1/N::value),1/N::value>{};

    template<typename N, typename M, typename... NS>
    struct div<N,M,NS...> : std::integral_constant<decltype(N::value/M::value),N::value/M::value>{};

    template<typename N, typename M, typename O, typename... NS>
    struct div<N,M,O,NS...> : div<std::integral_constant<decltype(N::value/M::value),N::value/M::value>,O,NS...>{};

    /**
    * Devuelve el modulo de dos enteros
    */
    template<typename N, typename M>
    struct mod : std::integral_constant<decltype(N::value%M::value),N::value%M::value>{};

    /**
    * Suma 1
    */
    template<typename N>
    struct add1 : std::integral_constant<decltype(N::value+1),N::value+1>{};

    /**
    * Resta 1
    */
    template<typename N>
    struct sub1 : std::integral_constant<decltype(N::value-1),N::value-1>{};

    /**
    * Valor absoluto de un entero
    */
    template<typename N>
    struct abs : std::integral_constant<decltype((N::value>=0)?(N::value):(-N::value)),(N::value>=0)?(N::value):(-N::value)>{};

    /**
    * Devuelve el maximo numero
    */
    template<typename N, typename... NS>
    struct max : N{};

    template<typename N, typename M, typename... NS>
    struct max<N,M,NS...> : max<std::integral_constant<decltype((N::value>M::value)?(N::value):(M::value)),(N::value>M::value)?(N::value):(M::value)>,NS...>{};

    /**
    * Devuelve el minimo numero
    */
    template<typename N, typename... NS>
    struct min : N{};

    template<typename N, typename M, typename... NS>
    struct min<N,M,NS...> : min<std::integral_constant<decltype((N::value<M::value)?(N::value):(M::value)),(N::value<M::value)?(N::value):(M::value)>,NS...>{};

    /**
    * Devuelve el maximo comun divisor
    */
    template<typename N, typename M>
    struct gcd_aux : gcd_aux<M,typename mod<N,M>::type>{};

    template<typename N>
    struct gcd_aux<N,std::integral_constant<decltype(0),0>> : N{};

    template<typename... NS>
    struct gcd : std::integral_constant<decltype(0),0>{};

    template<typename N, typename... NS>
    struct gcd<N,NS...> : N{};

    template<typename N, typename M, typename... NS>
    struct gcd<N,M,NS...> : gcd<typename gcd_aux<N,M>::type,NS...>{};

    /**
    * Devuelve el minimo comun multiplo
    */
    template<typename... NS>
    struct lcm : std::integral_constant<decltype(1),1>{};

    template<typename N, typename... NS>
    struct lcm<N,NS...> : N{};

    template<typename N, typename M, typename... NS>
    struct lcm<N,M,NS...> : lcm<typename div<typename abs<typename mult<N,M>::type>::type,typename gcd<N,M>::type>::type,NS...>{};

    //---- shortcuts ----

    template<int n>
    using int_constant_t = typename int_constant<n>::type;

    template<int n>
    static constexpr int int_constant_v = int_constant<n>::value;

    template<typename N>
    using is_zero_t = typename is_zero<N>::type;

    template<typename N>
    static constexpr bool is_zero_v = is_zero<N>::value;

    template<typename... NS>
    using plus_t = typename plus<NS...>::type;

    template<typename... NS>
    static constexpr int plus_v = plus<NS...>::value;

    template<typename... NS>
    using minus_t = typename minus<NS...>::type;

    template<typename... NS>
    static constexpr int minus_v = minus<NS...>::value;

    template<typename... NS>
    using mult_t = typename mult<NS...>::type;

    template<typename... NS>
    static constexpr int mult_v = mult<NS...>::value;

    template<typename... NS>
    using div_t = typename div<NS...>::type;

    template<typename... NS>
    static constexpr int div_v = div<NS...>::value;

    template<typename N, typename M>
    using mod_t = typename mod<N,M>::type;

    template<typename N, typename M>
    static constexpr int mod_v = mod<N,M>::value;

    template<typename N>
    using add1_t = typename add1<N>::type;

    template<typename N>
    static constexpr int add1_v = add1<N>::value;

    template<typename N>
    using sub1_t = typename sub1<N>::type;

    template<typename N>
    static constexpr int sub1_v = sub1<N>::value;

    template<typename N>
    using abs_t = typename abs<N>::type;

    template<typename N>
    static constexpr int abs_v = abs<N>::value;

    template<typename N, typename... NS>
    using max_t = typename max<N,NS...>::type;

    template<typename N, typename... NS>
    static constexpr int max_v = max<N,NS...>::value;

    template<typename N, typename... NS>
    using min_t = typename min<N,NS...>::type;

    template<typename N, typename... NS>
    static constexpr int min_v = min<N,NS...>::value;

    template<typename... NS>
    using gcd_t = typename gcd<NS...>::type;

    template<typename... NS>
    static constexpr int gcd_v = gcd<NS...>::value;

    template<typename... NS>
    using lcm_t = typename lcm<NS...>::type;

    template<typename... NS>
    static constexpr int lcm_v = lcm<NS...>::value;

}


#endif // INT_CONSTANT_H_INCLUDED
