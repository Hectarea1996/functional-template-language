#ifndef RATIONAL_H_INCLUDED
#define RATIONAL_H_INCLUDED


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
    struct rational_constant{
        using type = rational_constant<num,den>;
        using value_type = rational<int>;
        static constexpr rational<int> value = {num,den};
        constexpr operator value_type() const noexcept { return value; }
        constexpr value_type operator()() const noexcept { return value; }
    };

}


#endif // RATIONAL_H_INCLUDED
