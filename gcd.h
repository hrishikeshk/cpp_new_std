#include <limits.h>
#include <stdlib.h>

#include "numeric_funcs.h"

template <typename Int_Type>
Int_Type gcd(Int_Type i, Int_Type j){

	static_assert(std::is_convertible<Int_Type, unsigned long long int>::value, "Required, an integral type to invoke gcd functions");

	Int_Type g = i_gcd<Int_Type>(i, j);

	if(g >= (Int_Type)0)
		return g;

	Int_Type ret = abs(g);
	if(g < (Int_Type)0){
		if(ret < (Int_Type)0 || ret < g)
			return g;
	}
	return ret;
}

