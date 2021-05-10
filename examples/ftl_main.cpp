
#include <iostream>
#include "../constant/rational.h"
#include "../constant/equality.h"
#include "../constant/numeric.h"
#include "../list.h"


template<typename... TS>
struct print{};

template<typename T>
struct identity{
    using type = T;
};

template<typename N>
using build_simple = ftl::build_list<N,identity>;

int main(){

    using r1 = ftl::rational_constant<1,3>;
    using r2 = ftl::rational_constant<2,6>;

    using l1 = ftl::build_list_t<ftl::int_constant<3>,build_simple>;
    print<ftl::flatten_t<l1>>::type;

    std::cout << ftl::sub1_v<ftl::int_constant<2>> << std::endl;

    return 0;

}
