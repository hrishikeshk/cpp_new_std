#include <iostream>
#include "application.h"

int main(int argc, char **argv){

	auto app = Application::Instance();
	std::cout << "App created\n";
	for(int i = 0; i < argc; ++i){
		std::cout << "Argument : " << i << " : " << argv[i] << "\n";
	}
	app->run();
	app->Release();
	
	return 0;
}
