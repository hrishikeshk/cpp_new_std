#include <boost/asio/io_context.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>

#ifndef SERVER
#define SERVER

#include "Connection.h"
#include "ConnectionManager.h"

class Pool;

class Server{
  void do_accept();
  void do_await_stop();
  boost::asio::io_context io_context_;
  boost::asio::signal_set signals_;
  boost::asio::ip::tcp::acceptor acceptor_;
  ConnectionManager m_cm;
  
  Pool* m_pPool;
public:
  Server(const Server&) = delete;
  Server& operator=(const Server&) = delete;

  explicit Server(const std::string& address, const std::string& port, unsigned int num_threads);

  void run();
};

#endif
