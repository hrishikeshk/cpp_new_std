#include <boost/asio/io_context.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>
#include <vector>

#include <thread>

#ifndef SERVER
#define SERVER

#include "Connection.h"
#include "ConnectionManager.h"
/* https://theboostcpplibraries.com/boost.asio-scalability
 * https://www.bogotobogo.com/cplusplus/Boost/boost_AsynchIO_asio_tcpip_socket_server_client_timer_bind_handler_multithreading_synchronizing_C.php

 */
class Pool;

class Server{
  ////void sync_accept();
  void do_accept();
  void do_await_stop();
  
  //boost::asio::io_context io_context_;
  boost::asio::io_service io_service_;
  
  std::vector<boost::asio::io_service> v_io_svc;
  boost::asio::signal_set signals_;
  boost::asio::ip::tcp::acceptor acceptor_;
  ConnectionManager m_cm;
  unsigned int num_thr;
  Pool* m_pPool;
  
public:
  Server(const Server&) = delete;
  Server& operator=(const Server&) = delete;

  explicit Server(const std::string& address, const std::string& port, unsigned int num_threads);

  void run();
};

#endif
