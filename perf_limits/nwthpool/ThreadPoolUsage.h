#include <iostream>
#include <vector>

#ifndef THREAD_POOL_USAGE
#define THREAD_POOL_USAGE
#include "pool.h"
#include "TestWork.h"
namespace ThreadPoolUsage{
	void run(){
		std::cout << " ... Running Thread Pool Usage \n";
		auto pp = Pool::Instance();
	
		pp->start_io();
	
		pp->create_num(5);

		int a = 12345;
		std::function<int(int&)> fa = test_func_ii;
		pp->post_work_generic(fa, a);
	
		int b = 123456;
		std::function<int(int&)> fb = test_func_ii;
		pp->post_work_generic(fb, b);
	
		int c = 1234567;
		std::function<int(int&)> fc = test_func_ii;
		pp->post_work_generic(fc, c);
	
		std::string sa("a");
		std::function<bool(std::string&)> fsa = test_func_bs;
		pp->post_work_generic(fsa, sa);
	
		std::string sb("abcb");
		std::function<bool(std::string&)> fsb = test_func_bs;
		pp->post_work_generic(fsb, sb);
	
		int rd = 10;
		std::function<int(int&)> fsrefd = test_func_ii_ref;
		pp->post_work_generic(fsrefd, rd);

		pp->poll();
		
		std::cout << "Finished posting once. Posting more work\n";
		std::string sc("abcba");
		std::function<bool(std::string&)> fsc = test_func_bs;
		pp->post_work_generic(fsc, sc);

		pp->poll();
		
		std::cout << " ... Posted work. Posting more work in groups\n";
	
		std::vector<std::function<int(int&)>> vecfs;
		vecfs.push_back(fsrefd);
		vecfs.push_back(fsrefd);

		std::vector<int> vecdata;
		vecdata.push_back(2);
		vecdata.push_back(4);
	
		pp->post_work_generic_vec(vecfs, vecdata);
		
		std::cout << "Done all Posting work\n";
		
		pp->stop_io();
		Pool::Release();
	
		std::cout << " ... Releasing Pool\n";
	
		std::cout << "IO response from singly posted data: " << rd << "\n";
		std::cout << "IO response from grouped posted data: " << vecdata[0] << " : " << vecdata[1] << "\n";
	}
}
#endif
