#ifndef NUMERIC_FUNCS
#define NUMERIC_FUNCS

#include <stdlib.h>
#include <tuple>
#include <functional>

template <typename Int_Type>
Int_Type i_gcd(Int_Type i, Int_Type j){

	if(i == (Int_Type)0)
		return j;
	return i_gcd(j % i, i);
}

template<typename Int_Type>
std::tuple<Int_Type, Int_Type, Int_Type> i_extended_gcd(Int_Type i, Int_Type j){

	if(i == (Int_Type)0){
		return std::make_tuple<Int_Type, Int_Type, Int_Type>(0, 1, (Int_Type)j);
	}

	auto triple = i_extended_gcd(j % i, i);

	return std::make_tuple(std::get<1>(triple) - std::get<0>(triple)*(j / i), std::get<0>(triple), std::get<2>(triple));
}

template<typename Int_Type>
//Int_Type i_safe_modular_mult(Int_Type first, Int_Type second, Int_Type mod){
auto i_safe_modular_mult(Int_Type first, Int_Type second, Int_Type mod){

	if(second < 3){
		return ( first * second ) % mod;
	}
	else if(second & 1){
		return ( (first % mod) + i_safe_modular_mult( (first * 2) % mod, second / 2, mod) ) % mod;
	}
	else{
		return i_safe_modular_mult( (first * 2) % mod, second / 2, mod);
	}
}

template<typename Setter, typename Getter>
std::tuple<std::function<unsigned int()>, std::function<bool (unsigned int)>>
	sieve(unsigned int alloc_size, Setter set_func, Getter get_func){

	unsigned int m = 3, n = 3;
	auto index = ( ( (m * m) >> 1) - 1);

	while(index < alloc_size){
		set_func(index);
		index += m;
		if(index >= alloc_size){
			n += 2;
			m = n;
			index = ( ( (m * m) >> 1) - 1);
		}
	}
	return std::make_tuple(
				[=](){ 
					return alloc_size * 2 + 1; 
				},
				[&get_func,alloc_size](unsigned int query_num){ 
					if(query_num == 2)
						return false;
					if( !(query_num & 1))
						return true;
					if(query_num < 9)
						return false;
					auto target = (query_num / 2) - 1;
					if(target >= alloc_size)
						throw "Exception: Bad usage, out of bounds access";
					return get_func(target);
				}
			);
}

#endif

