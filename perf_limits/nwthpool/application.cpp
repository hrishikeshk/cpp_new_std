#include <iostream>
#include <vector>

#include "application.h"
#include "pool.h"
#include "TestWork.h"

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
	
	//pp->post_work();
	
	/*std::function<A(A)> f = [](A){ A a; std::cout << "Generic Work !\n "; return a;};
	A aa;
	pp->post_work_generic<A, A>(f, aa);
	*/
	
	int rd = 10;
	std::function<int(int&)> fsrefd = test_func_ii_ref;
	pp->post_work_generic(fsrefd, rd);
	
	int d = 10;
	std::function<char(int&)> fsd = test_func_ci;
	pp->post_work_generic(fsd, d);

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
	
	std::string sc("abcba");
	std::function<bool(std::string&)> fsc = test_func_bs;
	pp->post_work_generic(fsc, sc);

	pp->poll();
	
	std::cout << " ... Posted work\n";
	
	pp->stop_io();
	Pool::Release();
	
	std::cout << " ... Releasing Pool\n";
	
	std::cout << "IO response: " << rd << "\n";
}
