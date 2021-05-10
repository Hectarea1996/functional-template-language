#ifndef BOOLEAN_H_INCLUDED
#define BOOLEAN_H_INCLUDED

namespace ftl{

    //---- type ----

    template<bool b>
    using bool_constant = std::integral_constant<bool,b>;

}

#endif // BOOLEAN_H_INCLUDED
