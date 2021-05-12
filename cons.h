#ifndef CONS_H_INCLUDED
#define CONS_H_INCLUDED

namespace ftl{

    //---- types ----

    /// cons type
    template<typename T1, typename T2>
    struct cons{
        using type = cons<T1,T2>;
    };

    //---- methods ----

    /**
    * Devuelve el primer tipo de un cons
    */
    template<typename T>
    struct car{};

    template<typename T1, typename T2>
    struct car<cons<T1,T2>>{
        using type = T1;
    };

    /**
    * Devuelve el segundo tipo de un cons
    */
    template<typename T>
    struct cdr{};

    template<typename T1, typename T2>
    struct cdr<cons<T1,T2>>{
        using type = T2;
    };

    /**
    * Comprueba si un tipo es cons
    */
    template<typename T>
    struct is_pair : std::false_type {};

    template<typename T1, typename T2>
    struct is_pair<cons<T1,T2>> : std::true_type{};

    /**
    * Imprime un par
    */
    template<bool paren, typename T>
    struct cons_print_aux{
        static void exe(){
            std::cout << T::value;
        }
    };

    struct null;

    template<bool paren>
    struct cons_print_aux<paren,null>{
        static void exe(){
            std::cout << "( )";
        }
    };

    template<typename T>
    struct cons_print_aux<true, cons<T,null>>{
        static void exe(){
            std::cout << "( ";
            cons_print_aux<true,T>::exe();
            std::cout << " )";
        }
    };

    template<typename T>
    struct cons_print_aux<false, cons<T,null>>{
        static void exe(){
            cons_print_aux<true,T>::exe();
        }
    };

    template<typename T, typename S>
    struct cons_print_aux<true, cons<T,S>>{
        static void exe(){
            std::cout << "( ";
            cons_print_aux<true,T>::exe();
            std::cout << " . " << S::value << " )";
        }
    };

    template<typename T, typename S>
    struct cons_print_aux<false, cons<T,S>>{
        static void exe(){
            cons_print_aux<true,T>::exe();
            std::cout << " . " << S::value;
        }
    };

    template<typename T, typename S, typename SS>
    struct cons_print_aux<true,cons<T,cons<S,SS>>>{
        static void exe(){
            std::cout << "( ";
            cons_print_aux<true,T>::exe();
            std::cout << " ";
            cons_print_aux<false,cons<S,SS>>::exe();
            std::cout << " )";
        }
    };

    template<typename T, typename S, typename SS>
    struct cons_print_aux<false,cons<T,cons<S,SS>>>{
        static void exe(){
            cons_print_aux<true,T>::exe();
            std::cout << " ";
            cons_print_aux<false,cons<S,SS>>::exe();
        }
    };

    template<typename T>
    struct cons_print{
        static void exe(){
            std::cout << T::value << std::endl;
        }
    };

    template<>
    struct cons_print<null>{
        static void exe(){
            std::cout << "'( )" << std::endl;
        }
    };

    template<typename T, typename S>
    struct cons_print<cons<T,S>>{
        static void exe(){
            std::cout << "'";
            cons_print_aux<true,cons<T,S>>::exe();
            std::cout << std::endl;
        }
    };

    template<typename T>
    void cons_print_e(){
        cons_print<T>::exe();
    }


    //---- shortcuts ----

    template<typename T1, typename T2>
    using cons_t = typename cons<T1,T2>::type;

    template<typename T>
    using car_t = typename car<T>::type;

    template<typename T>
    using cdr_t = typename cdr<T>::type;

    template<typename T>
    using is_pair_t = typename is_pair<T>::type;

    template<typename T>
    static constexpr bool is_cons_v = is_pair<T>::value;

}

#endif // CONS_H_INCLUDED
