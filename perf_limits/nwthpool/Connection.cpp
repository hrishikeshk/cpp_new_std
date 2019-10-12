#include <iostream>
#include <string>

#include "Connection.h"
#include "ConnectionManager.h"
#include "pool.h"

Connection::Connection(boost::asio::ip::tcp::socket socket,
    ConnectionManager& manager)
  : m_socket(std::move(socket)),
    m_cm(manager){

}

void Connection::cm_stop(){
	m_cm.stop(shared_from_this());
}
