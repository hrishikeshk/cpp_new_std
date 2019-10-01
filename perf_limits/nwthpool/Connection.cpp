#include <iostream>
#include <string>

#include "Connection.h"
#include "ConnectionManager.h"

Connection::Connection(boost::asio::ip::tcp::socket socket,
    ConnectionManager& manager)
  : m_socket(std::move(socket)),
    m_cm(manager){
		
}

void Connection::start(){
  do_read();
}

void Connection::stop(){
  m_socket.close();
}

void Connection::do_read(){
  auto self(shared_from_this());
  m_socket.async_read_some(boost::asio::buffer(m_buffer),
      [this, self](boost::system::error_code ec, std::size_t bytes_transferred){
        if (!ec){
		  std::cout << "Reading buffer, num bytes : " << bytes_transferred << " ... \n";
		  for(auto c:m_buffer){
			  std::cout << c;
		  }
		  std::cout << "\n";
          ////buffer_.data(), bytes_transferred
		  ////do_read();if more data to read, based on indications from what was parsed so far.
		  // else replying now
		  boost::asio::socket_base::send_buffer_size option(BUFFSIZE);
		  m_socket.set_option(option);
		  m_write_buffer.push_back(boost::asio::buffer(reply));
		  do_write();
        }
        else if (ec != boost::asio::error::operation_aborted){
          m_cm.stop(shared_from_this());
        }
      });
}

void Connection::do_write(){
  auto self(shared_from_this());
  //boost::asio::write(m_socket, boost::asio::buffer(reply, reply.length()));
  
  boost::asio::async_write(m_socket, m_write_buffer,
      [this, self](boost::system::error_code ec, std::size_t s){
        if (!ec){
          boost::system::error_code ignored_ec;
          m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
        }

        if (ec != boost::asio::error::operation_aborted){
          m_cm.stop(shared_from_this());
        }
      });
	  
}
