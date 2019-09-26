#include <string>
#include <iostream>

template<typename Data, typename Result>
Result test_func(Data& d);

template<typename T1, typename T2>
T2 test_func_iit(T1& a){
	T2 t2;
	return t2; 
}

int test_func_ii(int* pa){
	int& a = *pa;
	int oa = a;
	int digits = 0;
	while(a){
		a /= 10;
		++digits;
	}
	std::cout << "Num digits in: " << oa << " = " << digits << "\n";
	return digits;
}

bool test_func_bs(std::string* pa){
	std::string& a = *pa;
	int i = 0, j = a.length() - 1;
	while(i < j){
		if(a[i] != a[j]){
			std::cout << "Is Palindrome: " << a << " = " << false << "\n";
			return false;
		}
		++i;
		--j;
	}
	std::cout << "Is Palindrome: " << a << " = " << true << "\n";
	return true;
}

char test_func_ci(int* pa){
	int& a = *pa;
	std::cout << "Negating: " << a << " = " << -a << "\n";
	a = -1 * a;
	return 'a';
}
