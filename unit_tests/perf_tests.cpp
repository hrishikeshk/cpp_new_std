#define BOOST_TEST_MODULE test_suite2
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <vector>
#include <time.h>

#include "Test_Utils.h"
#include "gcd.h"
#include "modulars.h"


using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE ( sieve_perf )

BOOST_AUTO_TEST_CASE( large_sieve_perf ){

	std::cout << "Running Test # " << "1\n";

	double regression_limit_sieve = 20.0;

        unsigned int allocate = (1 << 25);
        bool init = false;

        std::vector<bool> sieve_store(allocate, init);

        auto bound_setter = std::bind(simple_setter, &sieve_store, !init, std::placeholders::_1);
        auto bound_getter = std::bind(simple_getter, &sieve_store, std::placeholders::_1);

	time_t t_start = time(NULL);
        auto func_tuple = sieve(allocate, bound_setter, bound_getter);
	time_t t_sieve = time(NULL);

        auto alloc_func = std::get<0>(func_tuple);
        unsigned int allocated_ret = alloc_func();
        BOOST_REQUIRE(allocated_ret == allocate * 2 + 1);
        auto prime_getter = std::get<1>(func_tuple);

	BOOST_REQUIRE(prime_getter(2) == init);
        BOOST_REQUIRE(prime_getter(3) == init);
        BOOST_REQUIRE(prime_getter(5) == init);
        BOOST_REQUIRE(prime_getter(7) == init);
        BOOST_REQUIRE(prime_getter(11) == init);
        BOOST_REQUIRE(prime_getter(19) == init);
        BOOST_REQUIRE(prime_getter(101) == init);
        BOOST_REQUIRE(prime_getter(1759) == init);
        BOOST_REQUIRE(prime_getter(1000003) == init);


	BOOST_REQUIRE(prime_getter(9) == !init);
        BOOST_REQUIRE(prime_getter(12) == !init);
        BOOST_REQUIRE(prime_getter(51) == !init);
        BOOST_REQUIRE(prime_getter(57) == !init);
        BOOST_REQUIRE(prime_getter(78) == !init);
        BOOST_REQUIRE(prime_getter(110) == !init);
        BOOST_REQUIRE(prime_getter(1011) == !init);
        BOOST_REQUIRE(prime_getter(1 << 20) == !init);
        BOOST_REQUIRE(prime_getter( (1 << 20) - 1) == !init);


	double sieve_time = difftime(t_sieve, t_start); 
	std::cout << " Time for sieving = " << sieve_time << " seconds\n";

	BOOST_REQUIRE(sieve_time <= regression_limit_sieve);

	std::cout << " ... done\n";

}

BOOST_AUTO_TEST_CASE( seg_sieve_perf ){
	std::cout << "Running Test # " << "2\n";

	double regression_limit_sieve = 20.0;

        unsigned int allocate = (1 << 25);
        bool init = false;

        std::vector<bool> sieve_store(allocate, init);

        auto bound_setter = std::bind(simple_setter, &sieve_store, !init, std::placeholders::_1);
        auto bound_getter = std::bind(simple_getter, &sieve_store, std::placeholders::_1);

	time_t t_start = time(NULL);
        auto func_tuple = seg_sieve(allocate, bound_setter, bound_getter);
	time_t t_sieve = time(NULL);

        auto alloc_func = std::get<0>(func_tuple);
        unsigned int allocated_ret = alloc_func();
        BOOST_REQUIRE(allocated_ret == allocate * 2 + 1);
        auto prime_getter = std::get<1>(func_tuple);

	BOOST_REQUIRE(prime_getter(2) == init);
        BOOST_REQUIRE(prime_getter(3) == init);
        BOOST_REQUIRE(prime_getter(5) == init);
        BOOST_REQUIRE(prime_getter(7) == init);
        BOOST_REQUIRE(prime_getter(11) == init);
        BOOST_REQUIRE(prime_getter(19) == init);
        BOOST_REQUIRE(prime_getter(101) == init);
        BOOST_REQUIRE(prime_getter(1759) == init);
        BOOST_REQUIRE(prime_getter(1000003) == init);


	BOOST_REQUIRE(prime_getter(9) == !init);
        BOOST_REQUIRE(prime_getter(12) == !init);
        BOOST_REQUIRE(prime_getter(51) == !init);
        BOOST_REQUIRE(prime_getter(57) == !init);
        BOOST_REQUIRE(prime_getter(78) == !init);
        BOOST_REQUIRE(prime_getter(110) == !init);
        BOOST_REQUIRE(prime_getter(1011) == !init);
        BOOST_REQUIRE(prime_getter(1 << 20) == !init);
        BOOST_REQUIRE(prime_getter( (1 << 20) - 1) == !init);


	double sieve_time = difftime(t_sieve, t_start); 
	std::cout << " Time for sieving = " << sieve_time << " seconds\n";

	BOOST_REQUIRE(sieve_time <= regression_limit_sieve);

	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_SUITE_END()

