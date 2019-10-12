#ifndef POOL_H
#define POOL_H

#include <iostream>
#include <functional>
#include <array>
#include <vector>

#include <boost/asio/io_service.hpp>
#include <boost/thread/thread.hpp>

class Pool{
	static Pool* ms_instance;
	boost::asio::io_service ioService;
	boost::thread_group threadpool;
	//boost::asio::io_service::work* pwork;
	boost::asio::io_service::work work {ioService};

private:
	Pool(const Pool& rhs);
	Pool& operator=(const Pool& rhs);
	Pool();
	~Pool();

public:
	static Pool* Instance();
	static void Release();
	
	void create_num(int t);

	void start_io();
	void stop_io();
	
	template<typename WorkObj, typename ResultObj>
	void post_work_generic_vec(std::vector<std::function<ResultObj(WorkObj&)>>& vf, 
							std::vector<WorkObj>& vwo){
		for(unsigned int i = 0; i < vf.size(); ++i){
			const auto& bb = boost::bind(vf[i], std::ref(vwo[i]));
			ioService.post(bb);
		}
		ioService.poll();
	}

	template<typename WorkObj, typename ResultObj>
	void post_work_generic(std::function<ResultObj(WorkObj&)> f, 
						   WorkObj& wo){
		const auto& bb = boost::bind(f, std::ref(wo));
		ioService.post(bb);
	}
	
	void poll();
};

#endif // POOL_H
