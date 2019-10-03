#include <signal.h>
#include <utility>

#include "Server.h"
#include "pool.h"
#include "BusinessLogic.h"

Server::Server(const std::string& address, const std::string& port, unsigned int num_threads)
  : io_context_(1),
    signals_(io_context_),
    acceptor_(io_context_),
    m_cm(),
	m_pPool(Pool::Instance()){

  signals_.add(SIGINT);
  signals_.add(SIGTERM);
#if defined(SIGQUIT)
  signals_.add(SIGQUIT);
#endif // defined(SIGQUIT)

  do_await_stop();

  m_pPool->start_io();
  m_pPool->create_num(num_threads);

  boost::asio::ip::tcp::resolver resolver(io_context_);
  boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(address, port).begin();
  acceptor_.open(endpoint.protocol());
  acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  acceptor_.bind(endpoint);
  acceptor_.listen();

  do_accept();
}

void Server::run(){
  io_context_.run();
}

void Server::do_accept(){
  acceptor_.async_accept(
      [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket){
        if (!acceptor_.is_open()){
          return;
        }

        if (!ec){
		  auto conn_ptr = std::make_shared<Connection>(std::move(socket), m_cm);
          m_cm.start(conn_ptr);
		  std::function<void(Connection_ptr&)> fp = businesslogicfptr;
		  m_pPool->post_work_generic(fp, conn_ptr);
		  m_pPool->poll();
		  //fp(conn_ptr);
        }

        do_accept();
      });
}

void Server::do_await_stop(){
  signals_.async_wait(
      [this](boost::system::error_code /*ec*/, int /*signo*/){
        acceptor_.close();
        m_cm.stop_all();
      });
}
