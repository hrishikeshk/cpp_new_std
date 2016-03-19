#include <limits.h>
#include <stdlib.h>

template <typename Int_Type>
Int_Type i_gcd(Int_Type i, Int_Type j){

	if(i == (Int_Type)0)
		return j;
	return i_gcd(j % i, i);
}

