#ifndef POOL_H
#define POOL_H

#include <boost/asio/io_service.hpp>
#include <boost/thread/thread.hpp>

#include <array>

class Pool{
	static Pool* ms_instance;
	boost::asio::io_service ioService;
	boost::thread_group threadpool;
	boost::asio::io_service::work* pwork;

private:
	Pool(const Pool& rhs);
	Pool& operator=(const Pool& rhs);

public:
	static Pool* Instance();
	static void Release();
	
	void create_num(int t);

	void start_io();
	void stop_io();
	
	void post_work();
	
	void myTask(std::array<char, 4>&);
	void clearCache(char);
	void getSocialUpdates(int);

private:
	Pool();
	~Pool();

};

#endif // POOL_H
