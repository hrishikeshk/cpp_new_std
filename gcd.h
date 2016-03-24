#ifndef GCD_FUNCS
#define GCD_FUNCS

#include <tuple>
#include <limits>

#include "numeric_funcs.h"

template <typename Int_Type>
Int_Type gcd(Int_Type i, Int_Type j){

	static_assert(std::is_convertible<Int_Type, unsigned long long int>::value, "Required, an integral type to invoke gcd functions");

	Int_Type g = i_gcd<Int_Type>(i, j);

	if(g >= (Int_Type)0)
		return g;

	if(g == std::numeric_limits<Int_Type>::min())
		return g;
	else
		return -g;
/*
	Int_Type ret = abs(g);
	if(g < (Int_Type)0){
		if(ret < (Int_Type)0 || ret < g)
			return g;
	}
	return ret;
*/
}

template<typename Int_Type>
std::tuple<Int_Type, Int_Type, Int_Type> extended_gcd(Int_Type i, Int_Type j){

	static_assert(std::is_convertible<Int_Type, unsigned long long int>::value, "Required, an integral type to invoke extended gcd functions");

	auto triple = i_extended_gcd(i, j);

	Int_Type g = std::get<2>(triple);

	if(g >= (Int_Type)0)
		return triple;
	
	if(g == std::numeric_limits<Int_Type>::min())
		return std::make_tuple(std::get<0>(triple), std::get<1>(triple), g);
	else
		return std::make_tuple(std::get<0>(triple), std::get<1>(triple), -g);
/*
	Int_Type ret = abs(std::get<2>(triple));
	if(g < (Int_Type)0){
		if(ret < (Int_Type)0 || ret < g)
			return triple;
	}
	return std::make_tuple(std::get<0>(triple), std::get<1>(triple), ret);
*/
}

#endif

