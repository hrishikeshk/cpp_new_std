#include <vector>
#include <set>

#include <boost/thread/mutex.hpp>
#ifndef CONNECTION_MANAGER
#define CONNECTION_MANAGER

#include "Connection.h"

using Connection_ref = unsigned int;

class ConnectionManager{
public:
  ConnectionManager(const ConnectionManager&) = delete;
  ConnectionManager& operator=(const ConnectionManager&) = delete;

  //explicit ConnectionManager(unsigned int num_thrs);
  ConnectionManager();

  ////Connection_ref start(boost::asio::ip::tcp::socket& sock);
  void start(Connection_ptr cp);

  ////void stop(Connection_ref cr);
  void stop(Connection_ptr cp);

  void stop_all();

  /*Connection_ptr& use(Connection_ref cr){
	  return m_conns[cr];
  }
  */
  
private:
  ////std::vector<Connection_ptr> m_conns;
  std::set<Connection_ptr> m_conns;
  
  boost::mutex m_cmlock;
  std::vector<Connection_ref> m_freestack;
  unsigned int m_freetop;
};

#endif
