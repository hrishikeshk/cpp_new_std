#ifndef MODULAR_FUNCS
#define MODULAR_FUNCS

#include <limits>
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

#endif

