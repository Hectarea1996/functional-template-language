
#include <iostream>

#include "cons.h"
#include "null.h"
#include "list.h"
#include "constant/numeric.h"

template<typename... TS>
struct print{};


int main(){

    using lista1 = ftl::list_t<int,bool>;
    using lista2 = ftl::list_t<float,char,double>;
    using lista3 = ftl::append_t<lista1,lista2>;
    using lista4 = ftl::list_t<lista1,int,lista2>;

    //print<ftl::plus_t<>>::type;

    std::cout << ftl::div_v<ftl::abs_t<ftl::int_constant<-1>>> << std::endl;
    std::cout << ftl::div_v<ftl::int_constant<81>,ftl::int_constant<3>,ftl::int_constant<3>> << std::endl;

    std::cout << ftl::lcm_v<ftl::int_constant<12>,ftl::int_constant<10>> << std::endl;

    return 0;

}
