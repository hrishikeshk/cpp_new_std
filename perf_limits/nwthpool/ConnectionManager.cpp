#include <iostream>
#include "ConnectionManager.h"

/*
ConnectionManager::ConnectionManager(unsigned int num_thr)
	:m_freetop(num_thr),
	////m_conns(num_thr),
	m_freestack(num_thr){

		for(unsigned int i = 0; i < num_thr; ++i){
			m_conns[i] = std::make_shared<Connection>(*this);
		}
}
*/

ConnectionManager::ConnectionManager(){
}

void ConnectionManager::start(Connection_ptr cp){
  boost::unique_lock<boost::mutex> ul(m_cmlock);
  m_conns.insert(cp);
  //c->start();
}

void ConnectionManager::stop(Connection_ptr cp){
  boost::unique_lock<boost::mutex> ul(m_cmlock);
  cp->stop();
  //std::cout << "Socket : " << cr << " closed...\n";
}

/*Connection_ref ConnectionManager::start(boost::asio::ip::tcp::socket& s){
  boost::unique_lock<boost::mutex> ul(m_cmlock);
  if(m_freetop == 0){
	  return m_freetop - 1;
  }
  else{
	  --m_freetop;
	  m_conns[m_freetop]->set_socket(s);
  }
  return m_freetop;
  //m_conns.insert(c);
  ////c->start();
}

void ConnectionManager::stop(Connection_ref cr){
  boost::unique_lock<boost::mutex> ul(m_cmlock);
  m_conns[cr]->stop();
  std::cout << "Socket : " << cr << " closed...\n";
}
*/

void ConnectionManager::stop_all(){
  boost::unique_lock<boost::mutex> ul(m_cmlock);
  for (auto c: m_conns)
    c->stop();
  std::cout << "All connections cleared from Set and sockets closed\n";
}
