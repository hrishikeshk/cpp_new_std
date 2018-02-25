#define BOOST_TEST_MODULE test_suite1
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <stdlib.h>
#include <limits>
#include <tuple>

#include "Test_Utils.h"
#include "../pa/List.h"
#include "../pa/List_Functions.h"

using namespace boost::unit_test;

int test_number = 1;

template<typename T, typename U>
List<T>* create_list(int size, std::function<T*(U)> make_T, U& u){
  auto t = make_T(u);
  auto node = new Node<T>(*t);
  auto list = new List<T>(node);
  return list;
}

int* make_int(int x){
  return new int(x);
}

BOOST_AUTO_TEST_SUITE ( test_suite_mods )

BOOST_AUTO_TEST_CASE( simple1 ){
        std::cout << "Running Test # " << test_number++ << "\n";

        int u = 7;
        auto list1 = create_list<int, int>(1, make_int, u);
        BOOST_REQUIRE(*(kth_to_last(*list1, 0)) == u);

        std::cout << " ... done\n";
}

BOOST_AUTO_TEST_SUITE_END()

