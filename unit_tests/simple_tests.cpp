#define BOOST_TEST_MODULE test_suite1
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <stdlib.h>
#include <limits>

#include "Test_Utils.h"
#include "gcd.h"

using namespace boost::unit_test;

int test_number = 1;

BOOST_AUTO_TEST_SUITE ( test_suite1 )

BOOST_AUTO_TEST_CASE( simple35 ){
	std::cout << "Running Test # " << test_number++ << "\n";
	BOOST_REQUIRE( gcd(3, 5) == 1);
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
	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( simple30_45 ){
	std::cout << "Running Test # " << test_number++ << "\n";
	BOOST_REQUIRE( gcd(30, 45) == 15);
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
	int ans = gcd<int>(0x1 << 31, 0x1 << 31);
	BOOST_REQUIRE(ans == 0x1 << 31); //// Only in case of an INT_MIN, returning a negative.
	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_SUITE_END()

