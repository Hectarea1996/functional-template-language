
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

    using l1 = ftl::permutations_t<ftl::zip_t<ftl::range_t<ftl::int_constant<4>>,ftl::range_t<ftl::int_constant<4>>>>;
    //print<l1>::type;

    ftl::cons_print_e<l1>();

    return 0;

}
