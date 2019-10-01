#include <signal.h>
#include <utility>

#include "Server.h"

Server::Server(const std::string& address, const std::string& port)
  : io_context_(1),
    signals_(io_context_),
    acceptor_(io_context_),
    m_cm(){

  signals_.add(SIGINT);
  signals_.add(SIGTERM);
#if defined(SIGQUIT)
  signals_.add(SIGQUIT);
#endif // defined(SIGQUIT)

  do_await_stop();

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
          m_cm.start(std::make_shared<Connection>(
              std::move(socket), m_cm));
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
