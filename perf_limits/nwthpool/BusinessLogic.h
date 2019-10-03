#include <iostream>
#include <functional>
#include <string>

#ifndef BUSINESS_LOGIC
#define BUSINESS_LOGIC
#include "Connection.h"
#include "TestWork.h"

void businesslogicfptr(Connection_ptr& cp){
	std::function<bool(std::string&)> fp = test_func_bs;
	cp->start(fp);
}

#endif
