#include <limits.h>
#include <stdlib.h>

template <typename Int_Type>
Int_Type i_gcd(Int_Type i, Int_Type j){

	if(i == 0)
		return j;
	return i_gcd(j % i, i);
}

template <typename Int_Type>
Int_Type gcd(Int_Type i, Int_Type j){
	Int_Type g = i_gcd<Int_Type>(i, j);

	return abs(g); //// Might do abs() on an INT_MIN ... TODO
}

