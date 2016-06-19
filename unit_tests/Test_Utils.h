#ifndef TEST_UTILS
#define TEST_UTILS

#include <iostream>
#include <vector>
#include <bitset>

template <typename T, typename Func>
bool compare(const T& actual, const T& correct, int& test_number){

        bool is_correct = Func(actual, correct);
        if(is_correct){
                return true;
        }
        return false;
}

void simple_setter(std::vector<bool>* store, bool data, unsigned int offset){
	(*store)[offset] = data;
}

bool simple_getter(std::vector<bool>* store, unsigned int offset){
	return (*store)[offset];
}

void boolarr_setter(bool* store, bool data, unsigned int offset){
	store[offset] = data;
}

bool boolarr_getter(bool* store, unsigned int offset){
	return store[offset];
}

void bsarr_setter(std::bitset< 1<<25 >* store, bool data, unsigned int offset){
	(*store)[offset] = data;
}

bool bsarr_getter(std::bitset< 1<<25 >* store, unsigned int offset){
	return (*store)[offset];
}

#endif

