#include <signal.h>
#include <utility>
#include <iostream>

#include <thread>

#include "Server.h"
#include "pool.h"
#include "BusinessLogic.h"

Server::Server(const std::string& address, const std::string& port, unsigned int num_threads)
  : num_thr(num_threads),
    v_io_svc(num_threads),
	signals_(io_service_),
    acceptor_(io_service_),
    ////m_cm(num_threads),
	m_pPool(Pool::Instance()){

  signals_.add(SIGINT);
  signals_.add(SIGTERM);
#if defined(SIGQUIT)
  signals_.add(SIGQUIT);
#endif // defined(SIGQUIT)

  do_await_stop();

  m_pPool->start_io();
  m_pPool->create_num(num_threads);
/*
 * With Boost asio, there are two actions - 
 * the operation and the handler that runs after the operation is complete.
 * The operation could be async and thus multiple could be invoked at once.
 * Invoking the operation takes an io_service/context object.
 * run() on that io_service is blocking and its usually invoked from within a separate thread.
 * Boost.asio will invoke any handlers after the operation is complete in only
 * one of those threads that have invoked io_service.run() until then.
 * Fine so far.
 * Writing a network server and using Boost.asio async accept. 
 * We want to listen on one port.
 * Such a listener will be supplied a single instance of io_service. 
 * Understandably, only one acceptor will
 * be actually accepting/listening on the port.
 * Once a client connects, we want to run a handler. The accept handler is complex, long 
 running code.
 * We want to run each handler on separate threads and run handlers concurrently for each 
 incoming client
 * connection.
 * It appears that Boost.asio does not run handlers concurrently. 
 * The documentation provides examples with timers, and they work too. But what about a 
	case in accept
 * where only one thread may listen on the port ?
 * 
*/
  boost::asio::ip::tcp::resolver resolver(io_service_);
  boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(address, port).begin();
  acceptor_.open(endpoint.protocol());
  acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  acceptor_.bind(endpoint);
  acceptor_.listen();

  do_accept();
  ////sync_accept();
}

void Server::run(){
	////io_service_.run();
	for(unsigned int i = 0; i < num_thr; ++i){
		std::function<void()> fa = [this](){std::cout << "Running Svc... \n"; io_service_.run();};
		m_pPool->post_work_generic(fa);
	}
	m_pPool->poll();
	std::cout << "Out of run... \n";
	m_pPool->stop_io();
	Pool::Release();
}

void Server::do_accept(){
std::cout << "Trying async accept now ...";
  acceptor_.async_accept(
      [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket){
        if (!acceptor_.is_open()){
          return;
        }
std::cout << "Within accept. Proceeding to Posting ...";
        if (!ec){
		  auto conn_ptr = std::make_shared<Connection>(std::move(socket), m_cm);
          m_cm.start(conn_ptr);
		  std::function<void(Connection_ptr&)> fp = businesslogicfptr;
		  m_pPool->post_work_generic(fp, conn_ptr);
		  //m_pPool->poll();
		  ////fp(conn_ptr);
        }
std::cout << "Done accept and Posting. Proceeding to next accept ...\n";
        do_accept();
      });
std::cout << "After setting off async accept ... \n";
}

void Server::do_await_stop(){
  signals_.async_wait(
      [this](boost::system::error_code /*ec*/, int /*signo*/){
        acceptor_.close();
        m_cm.stop_all();
      });
}

/*
void Server::sync_accept(){
	while(true){
		if(!acceptor_.is_open()){
			continue;
		}
		boost::system::error_code ec;
		boost::asio::ip::tcp::socket socket = acceptor_.accept(ec);
		if(!ec){
		  auto conn_ref = m_cm.start(socket);
		  auto fp = std::make_shared<std::function<void(Connection_ptr)>>(businesslogicfptr);
		  ////m_pPool->post_work_generic(*fp, m_cm.use(conn_ref));
		  (*fp)(m_cm.use(conn_ref));
		}
		else{
			std::cout << "Error in accepting : " << ec.message() << "\n";
		}
	}
}
*/
