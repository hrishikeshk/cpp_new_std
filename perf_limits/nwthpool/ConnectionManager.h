#include <set>

#ifndef CONNECTION_MANAGER
#define CONNECTION_MANAGER

#include "Connection.h"

class ConnectionManager{
	public:
  ConnectionManager(const ConnectionManager&) = delete;
  ConnectionManager& operator=(const ConnectionManager&) = delete;

  ConnectionManager();

  void start(Connection_ptr c);

  void stop(Connection_ptr c);

  void stop_all();

private:
  std::set<Connection_ptr> m_conns;
};

#endif
