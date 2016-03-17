#define BOOST_TEST_MODULE test_suite1
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <stdlib.h>

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
	BOOST_REQUIRE( gcd(0x7fffffff, 1) == 1);
	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( extreme_top_2 ){
	std::cout << "Running Test # " << test_number++ << "\n";
	BOOST_REQUIRE( gcd(0x7fffffff, 0x7fffffff) == 0x7fffffff);
	BOOST_REQUIRE( gcd(0x7fffffff, 0x7ffffffe) == 1);
	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( extreme_neg_2 ){
	std::cout << "Running Test # " << test_number++ << "\n";
	BOOST_REQUIRE( gcd(-0x7fffffff, 0x7ffffffe) == 1);
	BOOST_REQUIRE( gcd(0x7fffffff, -0x7ffffffe) == 1);
	BOOST_REQUIRE( gcd(-0x7fffffff, -0x7ffffffe) == 1);

	BOOST_REQUIRE( gcd( (0x1 << 31), 0x7ffffffe) == 2);

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

