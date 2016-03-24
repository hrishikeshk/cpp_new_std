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

	return i_safe_modular_mult<Int_Type>(first % mod, second % mod, mod);
}

template<typename Int_Type>
Int_Type mod_mult_inverse(Int_Type num, Int_Type mod){ // General case ...

	if(!mod || !num)
		throw "Exception: Division by zero or zero as input";

	auto triplet = extended_gcd<Int_Type>(num, mod);
	if(std::get<2>(triplet) != 1){
		throw "Exception: Multiplicative inverse does not exist, the number and mod are not co-prime";
	}

	return std::get<0>(triplet);
}

template<typename Int_Type>
Int_Type safe_power(Int_Type num, Int_Type pow, Int_Type mod){
	if(pow < 2)
		return num % mod;

	Int_Type ans = safe_power(safe_modular_mult(num, num, mod), pow >> 1, mod);
	if(pow & 1)
		ans = safe_modular_mult(ans, num, mod);
	
	return ans;
}

template <typename Int_Type>
Int_Type flt_mod_mult_inverse(Int_Type num, Int_Type mod){ // mod must be known to be prime and num not be divisible by mod..

	if(!mod || !num)
		throw "Exception: Division by zero or zero as input";

	num = num % mod;
	if(num == 0)
		throw "Exception: Invalid use for Fermat's last theorem based call, mod divides num";

	if(mod < 3)
		return 1;

	return safe_power(num, mod - 2, mod);
}

#endif

