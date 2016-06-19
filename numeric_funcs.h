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

//Int_Type i_safe_modular_mult(Int_Type first, Int_Type second, Int_Type mod){
template<typename Int_Type>
auto i_safe_modular_mult(Int_Type first, Int_Type second, Int_Type mod) -> Int_Type{

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
/*
	unsigned int m = 3, n = 3;
	auto index_num = m * m;
	auto two_m = (m << 1);
*/

	if(alloc_size < 5)
		throw "Unsupported for allocation sizes less than 5 numbers";

	auto max_num = (alloc_size << 1) + 1;
	unsigned int m = 3, p, two_m = (m << 1);
	while(m * m <= max_num){
		if(!get_func( (m >> 1) - 1) ){
			p = m + two_m;
			while(p <= max_num){
				set_func( (p >> 1) - 1);
				p += two_m;
			}
		}
		m += 2;
		two_m = (m << 1);
	}

////
/*
	while(index_num <= max_num){
		set_func(( index_num >> 1) - 1);
		index_num += two_m;
		if(index_num > max_num){
			n += 2;
			m = n;
			two_m = (m << 1);
			index_num = m * m;
		}
	}
*/
	return std::make_tuple(
				[=](){ 
					return alloc_size * 2 + 1; 
				},
				[&get_func,alloc_size](unsigned int query_num){ 
					if(query_num == 2)
						return get_func(4);
					if( !(query_num & 1))
						return get_func(3);
					if(query_num < 9)
						return get_func(4);
					auto target = (query_num / 2) - 1;
					if(target >= alloc_size)
						throw "Exception: Bad usage, out of bounds access";
					return get_func(target);
				}
			);
}

template<typename Setter, typename Getter>
std::tuple<std::function<unsigned int()>, std::function<bool (unsigned int)>>
	seg_sieve(unsigned int alloc_size, Setter set_func, Getter get_func){

	if(alloc_size < 5)
		throw "Unsupported for allocation sizes less than 5 numbers";

	auto max_num = (alloc_size << 1) + 1;
	unsigned int sim_limit = sqrt(max_num);
	unsigned int m = 3, two_m = (m << 1), index_num;



 	unsigned int p;
	while(m * m <= sim_limit){
		if(!get_func( (m >> 1) - 1) ){
			p = m + two_m;
			while(p <= sim_limit){
				set_func( (p >> 1) - 1);
				p += two_m;
			}
		}
		m += 2;
		two_m = (m << 1);
	}


////

/*
	unsigned int n = 3;
	index_num = m * m;
	while(index_num <= sim_limit){
		set_func(( index_num >> 1) - 1);
		index_num += two_m;
		if(index_num > sim_limit){
			n += 2;
			m = n;
			two_m = (m << 1);
			index_num = m * m;
		}
	}
*/

	std::vector<unsigned int> primes;
	primes.push_back(3);
	primes.push_back(5);
	primes.push_back(7);
	for(unsigned int i = 4; i <= (sim_limit >> 1) - 1; ++i){
		if(get_func(i)){
			primes.push_back (((i + 1) << 1) + 1);
		}
	}

	unsigned int low_num =  (max_num % sim_limit) + 2;
	unsigned int high_num = low_num + sim_limit;
	unsigned int two_p;

	while(high_num <= max_num){

		for(auto p : primes){
			two_p = (p << 1);
			index_num = (low_num / p) * p;
			if(index_num & 1){
				if(index_num < low_num)
					index_num += two_p;
			}
			else{
				index_num += p;
			}
			while(index_num <= high_num){
				set_func( (index_num >> 1) - 1);
				index_num += two_p;
			}
		}
		low_num = high_num + 1;
		high_num = low_num + sim_limit;
	}

	return std::make_tuple(
				[=](){ 
					return alloc_size * 2 + 1; 
				},
				[&get_func,alloc_size](unsigned int query_num){ 
					if(query_num == 2)
						return get_func(4);
					if( !(query_num & 1))
						return get_func(3);
					if(query_num < 9)
						return get_func(4);
					auto target = (query_num / 2) - 1;
					if(target >= alloc_size)
						throw "Exception: Bad usage, out of bounds access";
					return get_func(target);
				}
		);
}

#endif

