#ifndef RATIONAL_H_INCLUDED
#define RATIONAL_H_INCLUDED

#include "quasi_integral.h"

namespace ftl{

    //---- type ----

    template<typename T>
    struct rational{
        T num;
        T den;

        template<typename S>
        constexpr bool operator == (const rational<S>& r) const{
            return this->den*r.num == this->num*r.den;
        }
    };

    template<int num, int den>
    struct rational_constant : quasi_integral_constant<rational<int>>{
        static constexpr rational<int> value = {num,den};
        constexpr operator value_type() const noexcept { return value; }
        constexpr value_type operator()() const noexcept { return value; }
    };

}


#endif // RATIONAL_H_INCLUDED
