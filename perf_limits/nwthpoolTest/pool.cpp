#include "pool.h"
#include <boost/bind.hpp>
#include <iostream>

Pool* Pool::ms_instance = nullptr;

Pool::Pool(){

}

Pool::~Pool(){
	//delete pwork;"
	try{
		threadpool.join_all();
	}
	catch(std::exception ex){
		std::cout << "Exception in Pool release and dtor\n";
	}
}

Pool* Pool::Instance(){
	if (ms_instance == nullptr) {
		ms_instance = new Pool();
	}
	return ms_instance;
}

void Pool::Release(){
	if (ms_instance) {
		delete ms_instance;
	}
	ms_instance = nullptr;
}

void Pool::create_num(int t){
	for(int i = 0; i < t; ++i){
		threadpool.create_thread(boost::bind(&boost::asio::io_service::run, &ioService) );
	}
}

void Pool::start_io(){
	//boost::asio::io_service::work work(ioService);
	//pwork = new boost::asio::io_service::work(ioService);
}

void Pool::stop_io(){
	ioService.stop();
}

void Pool::poll(){
	ioService.poll();
}

