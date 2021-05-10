#ifndef EQUALITY_H_INCLUDED
#define EQUALITY_H_INCLUDED

#include "boolean.h"

namespace ftl{

    //---- methods ----

    /// TODO: Elegir nombres buenos

    /**
    * Comprueba que dos constantes sean iguales
    */
    template<typename T, typename S>
    struct eq : bool_constant<T::value==S::value>{};

    /**
    * Comprueba que dos constantes sean diferentes
    */
    template<typename T, typename S>
    struct neq : bool_constant<T::value!=S::value>{};

    /**
    * Comprueba que dos constantes sean diferentes
    */
    template<typename T, typename S>
    struct lt : bool_constant<T::value<S::value>{};



    template<typename T, typename S>
    using eq_t = typename eq<T,S>::type;

    template<typename T, typename S>
    static constexpr bool eq_v = eq<T,S>::value;


}


#endif // EQUALITY_H_INCLUDED
