
#include <iostream>

#include "cons.h"
#include "null.h"
#include "list.h"

template<typename... TS>
struct print{};

int main(){

    using lista1 = ftl::list_t<int,bool>;
    using lista2 = ftl::list_t<float,char,double>;
    using lista3 = ftl::append_t<lista1,lista2>;
    using lista4 = ftl::list_t<lista1,int,lista2>;

    print<ftl::map_t<ftl::is_list,lista4>>::type;

    return 0;

}
