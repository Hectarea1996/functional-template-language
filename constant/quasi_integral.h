#ifndef QUASI_INTEGRAL_H_INCLUDED
#define QUASI_INTEGRAL_H_INCLUDED


namespace ftl{

    //---- type ----

    template<typename T>
    struct quasi_integral_constant{

        using value_type = T;
        using type = quasi_integral_constant<T>;

    };

}


#endif // QUASI_INTEGRAL_H_INCLUDED
