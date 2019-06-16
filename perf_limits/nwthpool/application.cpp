#include "application.h"
#include <iostream>
#include "pool.h"

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
	std::cout << " ... Running App \n";
	auto pp = Pool::Instance();
	
	pp->start_io();
	
	pp->create_num(5);
	
	pp->post_work();
	
	std::cout << " ... Posted work\n";
	
	pp->stop_io();
	Pool::Release();
	
	std::cout << " ... Releasing Pool\n";
}
