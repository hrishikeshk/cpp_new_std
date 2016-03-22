#ifndef MODULAR_FUNCS
#define MODULAR_FUNCS

#include <limits>
#include <tuple>
#include "gcd.h"
#include "numeric_funcs.h"

template<typename Int_Type>
Int_Type safe_modular_mult(Int_Type first, Int_Type second, Int_Type mod){

	if(!mod)
		throw "Exception: Division by zero";

	if(first < second){
		Int_Type t = first;
		first = second;
		second = t;
	}
	Int_Type max = std::numeric_limits<Int_Type>::max();
	if( (max - mod) < mod){
		if( ((max - first) < first) && (first < mod) && (second > 1))
			throw "Exception: Can't avoid overflowing.";
	}

	static_assert(std::is_convertible<Int_Type, unsigned long long int>::value, "Required, an integral type to use modular multiplication");

	return i_safe_modular_mult(first % mod, second % mod, mod);
}

template<typename Int_Type>
Int_Type mod_mult_inverse(Int_Type num, Int_Type mod){ // General case ...

	if(!mod)
		throw "Exception: Division by zero";

	auto triplet = extended_gcd(num, mod);
	if(std::get<2>(triplet) != 1){
		throw "Exception: Multiplicative inverse does not exist, the number and mod are not co-prime";
	}

	return std::get<0>(triplet);
}

template <typename Int_Type>
Int_Type fl_mod_mult_inverse(Int_Type num, Int_Type mod){ // mod must be known to be prime and num not be divisible by mod..

	if(!mod)
		throw "Exception: Division by zero";

	num = num % mod;
	if(num == 0)
		throw "Exception: Invalid use for Fermat's last theorem based call, mod divides num";

	Int_Type tmp;
	Int_Type pow = mod - 2;
	while(pow > 1){
		if(pow & 1)
			tmp = num;
		num = safe_modular_mult(num, num, mod);
		if(pow & 1)
			num = safe_modular_mult(num, tmp, mod);
		pow >>= 1;
	}
	return num;
}

#endif

