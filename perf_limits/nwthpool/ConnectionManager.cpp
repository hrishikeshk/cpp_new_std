#include <iostream>
#include "ConnectionManager.h"

ConnectionManager::ConnectionManager(){
}

void ConnectionManager::start(Connection_ptr c){
  boost::unique_lock<boost::mutex> ul(m_cmlock);
  m_conns.insert(c);
  ////c->start();
}

void ConnectionManager::stop(Connection_ptr c){
  boost::unique_lock<boost::mutex> ul(m_cmlock);
  m_conns.erase(c);
  c->stop();
  std::cout << "Connection from Set cleaned\n";
}

void ConnectionManager::stop_all(){
  boost::unique_lock<boost::mutex> ul(m_cmlock);
  for (auto c: m_conns)
    c->stop();
  m_conns.clear();
  std::cout << "All connections cleared from Set and sockets closed\n";
}
