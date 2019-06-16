#include <iostream>
#include "application.h"

int main(int argc, char **argv){

	auto app = Application::Instance();
	std::cout << "App created\n";
	app->run();
	app->Release();
	
	return 0;
}
