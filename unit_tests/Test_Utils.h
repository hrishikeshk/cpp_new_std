#ifndef TEST_UTILS
#define TEST_UTILS

#include <iostream>
#include <vector>

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

#endif

