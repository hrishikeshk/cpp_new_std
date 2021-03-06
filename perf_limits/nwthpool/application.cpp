#include <iostream>
#include <vector>

#include "application.h"
//#include "ThreadPoolUsage.h"
#include "Server.h"

Application* Application::ms_instance = nullptr;

Application::Application(){

}

Application::~Application(){
	
}

Application* Application::Instance(){
	if (ms_instance == nullptr){
		ms_instance = new Application();
	}
	return ms_instance;
}

void Application::Release(){
	if (ms_instance) {
		delete ms_instance;
	}
	ms_instance = nullptr;
}

void Application::run(){
	std::cout << " ... Running Apps \n";
	
	////ThreadPoolUsage::run();
	Server s("127.0.0.1", "8080", 5);
	s.run();

	std::cout << "Finished Server \n";
}
