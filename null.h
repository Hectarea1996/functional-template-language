#ifndef NULL_H_INCLUDED
#define NULL_H_INCLUDED


namespace ftl{

    //---- types ----

    /// null type
    struct null{
        using type = null;
    };

    //---- methods ----

    /**
    * Comprueba si un tipo es null
    */
    template<typename T>
    struct is_null : std::false_type{};

    template<>
    struct is_null<null> : std::true_type{};

    //---- shortcuts ----

    using null_t = null::type;

    template<typename T>
    using is_null_t = typename is_null<T>::type;

    template<typename T>
    static constexpr bool is_null_v = is_null<T>::value;

}

#endif // NULL_H_INCLUDED
