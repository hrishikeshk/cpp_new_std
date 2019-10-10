#include <functional>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

#include "Client.h"
#include "pool.h"

using boost::asio::ip::tcp;

int main(int argc, char* argv[]){
  try{
	auto p = Pool::Instance();
	p->start_io();
	unsigned int num_thrs = 4;
	p->create_num(num_thrs);
	std::function<int(std::string&)> fp = call_wrapper;
	std::vector<std::function<int(std::string&)>> vfs;
	std::vector<std::string> vwo;
	std::string t = "hkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkpkkkkkkkkkkkkkkkkkkkkkkkkkkkh";
	for(unsigned int i = 0; i < num_thrs; ++i){
		vfs.push_back(fp);
		vwo.push_back(t);
	}
	p->post_work_generic_vec(vfs, vwo);
	p->poll();
	
	p->stop_io();
	Pool::Release();
  }
  catch (std::exception& e){
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
