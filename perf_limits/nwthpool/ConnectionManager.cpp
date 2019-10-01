#include "ConnectionManager.h"

ConnectionManager::ConnectionManager(){
}

void ConnectionManager::start(Connection_ptr c){
  m_conns.insert(c);
  c->start();
}

void ConnectionManager::stop(Connection_ptr c){
  m_conns.erase(c);
  c->stop();
}

void ConnectionManager::stop_all(){
  for (auto c: m_conns)
    c->stop();
  m_conns.clear();
}