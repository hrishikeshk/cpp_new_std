#include <stdlib.h>
#include <tuple>

template <typename Int_Type>
Int_Type i_gcd(Int_Type i, Int_Type j){

	if(i == (Int_Type)0)
		return j;
	return i_gcd(j % i, i);
}

template<typename Int_Type>
std::tuple<Int_Type, Int_Type, Int_Type> i_extended_gcd(Int_Type i, Int_Type j){

	if(i == (Int_Type)0){
		return std::make_tuple(0, 1, j);
	}

	auto triple = i_extended_gcd(j % i, i);

	return std::make_tuple(std::get<1>(triple) - std::get<0>(triple)*(j / i), std::get<0>(triple), std::get<2>(triple));
}

