
#include <iostream>
#include "../constant/rational.h"
#include "../constant/equality.h"
#include "../constant/numeric.h"
#include "../constant/array.h"
#include "../list.h"
#include "../cons.h"


template<typename... TS>
struct print{};

template<typename T>
struct identity{
    using type = T;
};

template<typename N>
using build_simple = ftl::build_list<N,identity>;


static constexpr char s[] = "Hola mundo estatico.";

int main(){

    using r1 = ftl::rational_constant<1,3>;
    using r2 = ftl::rational_constant<2,6>;

    using l1 = ftl::build_list_t<ftl::int_constant<3>,build_simple>;
    using flat1 = ftl::flatten_t<l1>;
//    print<std::integral_constant<int,0>::value_type>::type;
//    print<decltype(ftl::list_to_array_constant_t<flat1>::value)>::type;

    std::cout << ftl::array_length_v<ftl::list_to_array_constant_t<flat1>> << std::endl;

    return 0;

}
