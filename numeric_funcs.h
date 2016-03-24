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
		return std::make_tuple<Int_Type, Int_Type, Int_Type>(0, 1, j);
	}

	auto triple = i_extended_gcd(j % i, i);

	return std::make_tuple(std::get<1>(triple) - std::get<0>(triple)*(j / i), std::get<0>(triple), std::get<2>(triple));
}

int f(double a, int b){
std::cout << "a = " << a << " , b = " << b << "\n";
	return 0;
}

template<typename Int_Type>
Int_Type i_safe_modular_mult(Int_Type first, Int_Type second, Int_Type mod){

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

/*
 * This code should compile - TODO
////////////////////////////////////
std::function<int(double, int)> fo = f;
auto func_with_ = std::bind(f,0,_1);
auto tuple = std::make_tuple(fo, func_with_);

auto f1 = std::get<0>(tuple);
f1(2.1, 4);

auto f2 = std::get<1>(tuple);
//f2(8);
func_with_(8);

//////////////////////////////////
*/
/*
template<typename Setter, typename Getter>
std::tuple<std::function<unsigned int()>, std::function<bool (Getter, unsigned int)>> 
	sieve(unsigned int alloc_size, Setter set_func, Getter get_func){

	unsigned int m = 3, n = 3;
	auto index = ( (m * n) / 2 - 1);

	while(index < alloc_size){
		set_func(index);
		n += 2;
		index = ( (m * n) / 2 - 1);
		if(index >= alloc_size){
			m += 2;
			n = m;
			index = ( (m * n) / 2 - 1);
		}
	}

	return std::make_tuple(
				[&](){ 
					return (alloc_size + 1) * 2; 
				},
				[&](Getter get_func, unsigned int query_num){ 
					auto target = (query_num / 2) - 1;
					if(target >= alloc_size)
						throw "Exception: Bad usage, out of bounds access";
					return get_func(target);
				}
			);
}
*/

#endif

