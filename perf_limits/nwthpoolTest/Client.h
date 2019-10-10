#ifndef CLIENT
#define CLIENT

#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum { max_length = 1024 };

struct InputArgs{
	int argc;
	char** argv;
	std::string& request;
};

int client_call(std::string& request){
	std::cout << "In Client Start\n";
  try{
    boost::asio::io_context io_context;

    tcp::socket s(io_context);
    tcp::resolver resolver(io_context);
    ////boost::asio::connect(s, resolver.resolve(argv[1], argv[2]));
	boost::asio::connect(s, resolver.resolve("127.0.0.1", "8080"));

    size_t request_length = request.length();
    boost::asio::write(s, boost::asio::buffer(request.c_str(), request_length));

    char reply[max_length];
    size_t reply_length = s.read_some(boost::asio::buffer(reply, max_length));
    std::cout << "Reply is: ";
    std::cout.write(reply, reply_length);
    std::cout << "\n";
	
	s.close();
	std::cout << "In Client End\n";
  }
  catch (std::exception& e){
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}

int call_wrapper(std::string& ia){
	return client_call(ia);
}

#endif
