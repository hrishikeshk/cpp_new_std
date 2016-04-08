#define BOOST_TEST_MODULE test_suite1
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <stdlib.h>
#include <limits>
#include <tuple>

#include "Test_Utils.h"
#include "gcd.h"
#include "modulars.h"

using namespace boost::unit_test;

int test_number = 1;

BOOST_AUTO_TEST_SUITE ( test_suite_mods )

BOOST_AUTO_TEST_CASE( simple12 ){
        std::cout << "Running Test # " << test_number++ << "\n";

        BOOST_REQUIRE( safe_modular_mult(1, 2, 2) == 0);
        BOOST_REQUIRE( safe_modular_mult(2, 1, 4) == 2);
        BOOST_REQUIRE( safe_modular_mult(10, 2, 3) == 2);
        BOOST_REQUIRE( safe_modular_mult(11, 22, 5) == 2);
        BOOST_REQUIRE( safe_modular_mult(213, 211235, 2) == 1);
        BOOST_REQUIRE( safe_modular_mult(0x7fffffff, 1, 2) == 1);
        BOOST_REQUIRE( safe_modular_mult(0x7fffffff, 0x7fffffff, 2) == 1);
        BOOST_REQUIRE( safe_modular_mult(0x7fffffff, 0x7fffffff, 5) == 4);

	int inv = mod_mult_inverse(15, 7);
	BOOST_REQUIRE( ( (inv * 15) % 7) == 1);

	inv = mod_mult_inverse(8, 15);
	BOOST_REQUIRE( ( (inv * 8) % 15) == 1);

	inv = flt_mod_mult_inverse(15, 7);
	BOOST_REQUIRE( ( (inv * 15) % 7) == 1);

	inv = flt_mod_mult_inverse(8, 5);
	BOOST_REQUIRE( ( (inv * 8) % 5) == 1);

	unsigned long long int inv_ull = mod_mult_inverse<unsigned long long int>(0x7fffffff, 1000003);
	BOOST_REQUIRE( ( (inv_ull * 0x7fffffff) % 1000003) == 1);

	inv_ull = mod_mult_inverse<unsigned long long int>(4, 1000003);
	BOOST_REQUIRE( ( (inv_ull * 4) % 1000003) == 1);

///////////

	inv_ull = flt_mod_mult_inverse<unsigned long long int>(4, 1000003);
	BOOST_REQUIRE( ( (inv_ull * 4) % 1000003) == 1);

	inv_ull = flt_mod_mult_inverse<unsigned long long int>(0x7fffffff, 1000003);
	BOOST_REQUIRE( ( (inv_ull * 0x7fffffff) % 1000003) == 1);

        std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( exceptions ){
	std::cout << "Running Test # " << test_number++ << "\n";
	bool thrown = false;
	try{
		safe_modular_mult(341, 4545, 0);
	}
	catch(...){
		thrown = true;
	}
	BOOST_REQUIRE(thrown == true);

	thrown = false;
	try{
		safe_modular_mult(0x7ffffffe, 2, 0x7fffffff);
	}
	catch(...){
		thrown = true;
	}
	BOOST_REQUIRE(thrown == true);

	thrown = false;
	try{
		mod_mult_inverse(27, 21);
	}
	catch(...){
		thrown = true;
	}
	BOOST_REQUIRE(thrown == true);

	thrown = false;
	try{
		flt_mod_mult_inverse(42, 21);
	}
	catch(...){
		thrown = true;
	}
	BOOST_REQUIRE(thrown == true);

	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE ( test_suite_gcd )

BOOST_AUTO_TEST_CASE( simple35 ){
	std::cout << "Running Test # " << test_number++ << "\n";
	BOOST_REQUIRE( gcd(3, 5) == 1);

	auto result = extended_gcd(3, 5);
	BOOST_REQUIRE(std::get<2>(result) == 1);
	int x = std::get<0>(result);
	int y = std::get<1>(result);
	BOOST_REQUIRE( (x * 3 + y * 5) == 1);

	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( simple53 ){
	std::cout << "Running Test # " << test_number++ << "\n";
	BOOST_REQUIRE( gcd(5, 3) == 1);
	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( simple24 ){
	std::cout << "Running Test # " << test_number++ << "\n";
	BOOST_REQUIRE( gcd(2, 4) == 2);

	auto result = extended_gcd(2, 4);
	BOOST_REQUIRE(std::get<2>(result) == 2);
	int x = std::get<0>(result);
	int y = std::get<1>(result);
	BOOST_REQUIRE( (x * 2 + y * 4) == 2);

	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( simple30_45 ){
	std::cout << "Running Test # " << test_number++ << "\n";
	BOOST_REQUIRE( gcd(30, 45) == 15);

	auto result = extended_gcd(30, 45);
	BOOST_REQUIRE(std::get<2>(result) == 15);
	int x = std::get<0>(result);
	int y = std::get<1>(result);
	BOOST_REQUIRE( (x * 30 + y * 45) == 15);

	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( neg_sim ){
	std::cout << "Running Test # " << test_number++ << "\n";
	BOOST_REQUIRE( gcd(-36, 45) == 9);
	BOOST_REQUIRE( gcd(64, -32) == 32);
	BOOST_REQUIRE( gcd(-88, -110) == 22);
	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( extreme_1 ){
	std::cout << "Running Test # " << test_number++ << "\n";
	BOOST_REQUIRE( gcd(std::numeric_limits<int>::max(), 1) == 1);
	BOOST_REQUIRE( gcd(std::numeric_limits<int>::max(), 0) == std::numeric_limits<int>::max());
	BOOST_REQUIRE( gcd(0, 0) == 0);
	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( extreme_top_2 ){

	int int_max = std::numeric_limits<int>::max();
	unsigned int uint_max = std::numeric_limits<unsigned int>::max();
	long long int long_max = std::numeric_limits<long long int>::max();
	unsigned long long int ulong_max = std::numeric_limits<unsigned long long int>::max();

	std::cout << "Running Test # " << test_number++ << "\n";
	BOOST_REQUIRE( gcd(int_max, int_max) == int_max);
	BOOST_REQUIRE( gcd(int_max, int_max - 1) == 1);

	BOOST_REQUIRE( gcd<unsigned int>(uint_max, uint_max) == uint_max);
	BOOST_REQUIRE( gcd<unsigned int>(uint_max, uint_max - 1) == 1);


	BOOST_REQUIRE( gcd<long long int>(long_max, long_max) == long_max);
	BOOST_REQUIRE( gcd<long long int>(long_max, long_max - 1) == 1);

	BOOST_REQUIRE( gcd<unsigned long long int>(ulong_max, ulong_max) == ulong_max);
	BOOST_REQUIRE( gcd<unsigned long long int>(ulong_max, ulong_max - 1) == 1);

	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( extreme_neg_2 ){
	int int_max = std::numeric_limits<int>::max();
	int int_min = std::numeric_limits<int>::min();

	std::cout << "Running Test # " << test_number++ << "\n";
	BOOST_REQUIRE( gcd(int_min + 1, int_max) == int_max);

	BOOST_REQUIRE( gcd(int_min, int_max) == 1);
	BOOST_REQUIRE( gcd(int_max, int_min + 1) == int_max);
	BOOST_REQUIRE( gcd(int_min, int_min + 1) == 1);

	BOOST_REQUIRE( gcd( (0x1 << 31), int_max - 1) == 2);

	BOOST_REQUIRE( gcd( (0x1 << 31), 2*2*2*2*3*5) == 2*2*2*2);

	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( extreme_2_neg_min ){
	std::cout << "Running Test # " << test_number++ << "\n";
	int ans = gcd<int>(1 << 31, 1 << 31);
	BOOST_REQUIRE(ans == (1 << 31) ); //// Only in case of an INT_MIN, returning a negative.
	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_SUITE_END()

void run_sieve(){

	unsigned int allocate = (1 << 20);
	bool init = false;
	
	std::vector<bool> sieve_store(allocate, init);

	auto bound_setter = std::bind(simple_setter, &sieve_store, !init, std::placeholders::_1);
	auto bound_getter = std::bind(simple_getter, &sieve_store, std::placeholders::_1);

	auto func_tuple = sieve(allocate, bound_setter, bound_getter);

	auto alloc_func = std::get<0>(func_tuple);
	unsigned int allocated_ret = alloc_func();
	BOOST_REQUIRE(allocated_ret == allocate * 2 + 1);
	auto prime_getter = std::get<1>(func_tuple);

//primes
	BOOST_REQUIRE(prime_getter(2) == init);
	BOOST_REQUIRE(prime_getter(3) == init);
	BOOST_REQUIRE(prime_getter(5) == init);
	BOOST_REQUIRE(prime_getter(7) == init);
	BOOST_REQUIRE(prime_getter(11) == init);
	BOOST_REQUIRE(prime_getter(19) == init);
	BOOST_REQUIRE(prime_getter(101) == init);
	BOOST_REQUIRE(prime_getter(1759) == init);
	BOOST_REQUIRE(prime_getter(1000003) == init);

//non-primes
	BOOST_REQUIRE(prime_getter(9) == !init);
	BOOST_REQUIRE(prime_getter(12) == !init);
	BOOST_REQUIRE(prime_getter(51) == !init);
	BOOST_REQUIRE(prime_getter(57) == !init);
	BOOST_REQUIRE(prime_getter(78) == !init);
	BOOST_REQUIRE(prime_getter(110) == !init);
	BOOST_REQUIRE(prime_getter(1011) == !init);
	BOOST_REQUIRE(prime_getter(1 << 20) == !init);
	BOOST_REQUIRE(prime_getter( (1 << 20) - 1) == !init);
}

void run_seg_sieve(){

	unsigned int allocate = (1 << 20);
	bool init = false;
	
	std::vector<bool> sieve_store(allocate, init);

	auto bound_setter = std::bind(simple_setter, &sieve_store, !init, std::placeholders::_1);
	auto bound_getter = std::bind(simple_getter, &sieve_store, std::placeholders::_1);

	auto func_tuple = seg_sieve(allocate, bound_setter, bound_getter);

	auto alloc_func = std::get<0>(func_tuple);
	unsigned int allocated_ret = alloc_func();
	BOOST_REQUIRE(allocated_ret == allocate * 2 + 1);
	auto prime_getter = std::get<1>(func_tuple);

//primes
	BOOST_REQUIRE(prime_getter(2) == init);
	BOOST_REQUIRE(prime_getter(3) == init);
	BOOST_REQUIRE(prime_getter(5) == init);
	BOOST_REQUIRE(prime_getter(7) == init);
	BOOST_REQUIRE(prime_getter(11) == init);
	BOOST_REQUIRE(prime_getter(19) == init);
	BOOST_REQUIRE(prime_getter(101) == init);
	BOOST_REQUIRE(prime_getter(1759) == init);
	BOOST_REQUIRE(prime_getter(1000003) == init);

//non-primes
	BOOST_REQUIRE(prime_getter(9) == !init);
	BOOST_REQUIRE(prime_getter(12) == !init);
	BOOST_REQUIRE(prime_getter(51) == !init);
	BOOST_REQUIRE(prime_getter(57) == !init);
	BOOST_REQUIRE(prime_getter(78) == !init);
	BOOST_REQUIRE(prime_getter(110) == !init);
	BOOST_REQUIRE(prime_getter(1011) == !init);
	BOOST_REQUIRE(prime_getter(1 << 20) == !init);
	BOOST_REQUIRE(prime_getter( (1 << 20) - 1) == !init);
}

BOOST_AUTO_TEST_SUITE ( test_suite_sieve )

BOOST_AUTO_TEST_CASE( simple_sieve_small ){
	std::cout << "Running Test # " << test_number++ << "\n";

	run_sieve();

	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( seg_sieve_small ){
	std::cout << "Running Test # " << test_number++ << "\n";

	run_seg_sieve();

	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( exception_sieve_small ){
	std::cout << "Running Test # " << test_number++ << "\n";

	unsigned int allocate = (25);
	bool init = false;
	
	std::vector<bool> sieve_store(allocate, init);

	auto bound_setter = std::bind(simple_setter, &sieve_store, !init, std::placeholders::_1);
	auto bound_getter = std::bind(simple_getter, &sieve_store, std::placeholders::_1);

	auto func_tuple = sieve(allocate, bound_setter, bound_getter);
	auto prime_getter = std::get<1>(func_tuple);

	BOOST_REQUIRE(prime_getter(51) == !init);

	bool thrown = false;
	try{
		prime_getter(53);
	}
	catch(...){
		thrown = true;
	}
	BOOST_REQUIRE(thrown == true);

	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( exception_seg_sieve_small ){
	std::cout << "Running Test # " << test_number++ << "\n";

	unsigned int allocate = (25);
	bool init = false;
	
	std::vector<bool> sieve_store(allocate, init);

	auto bound_setter = std::bind(simple_setter, &sieve_store, !init, std::placeholders::_1);
	auto bound_getter = std::bind(simple_getter, &sieve_store, std::placeholders::_1);

	auto func_tuple = seg_sieve(allocate, bound_setter, bound_getter);
	auto prime_getter = std::get<1>(func_tuple);

	BOOST_REQUIRE(prime_getter(51) == !init);

	bool thrown = false;
	try{
		prime_getter(53);
	}
	catch(...){
		thrown = true;
	}
	BOOST_REQUIRE(thrown == true);

	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_SUITE_END()

