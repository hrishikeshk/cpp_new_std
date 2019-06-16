#include "pool.h"
#include <boost/bind.hpp>
#include <iostream>

Pool* Pool::ms_instance = nullptr;

Pool::Pool(){

}

Pool::~Pool(){
	//delete pwork;
	threadpool.join_all();
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

void Pool::post_work(){
	std::array<char, 4> a;
	a[0] = '7'; a[1] = '7'; a[2] = '8'; a[3] = '6';
	const auto& bb = boost::bind(&Pool::myTask, this, a);
	ioService.post(bb);

	ioService.poll();

	ioService.post(boost::bind(&Pool::clearCache, this, 'Y'));
	ioService.post(boost::bind(&Pool::getSocialUpdates, this, 7786));
	std::cout << "... ... Finishing posting\n";
	ioService.poll();
}

void Pool::myTask(std::array<char, 4>& p){
	std::cout << p[0] << "\n";
}

void Pool::clearCache(char p){
	std::cout << p << "\n";
}

void Pool::getSocialUpdates(int p){
	std::cout << p << "\n";
}
