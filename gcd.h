
template <typename Int_Type>
Int_Type gcd(Int_Type i, Int_Type j){

	if(i == 0)
		return j;
	return gcd(j % i, i);
}

