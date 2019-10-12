#include <iostream>
#include <array>
#include <boost/asio.hpp>
#include <functional>
#include <string>

#ifndef CONNECTION
#define CONNECTION

static int x = 0;

const unsigned int BUFFSIZE = 8192;
class ConnectionManager;

class Connection : public std::enable_shared_from_this<Connection>{
	boost::asio::ip::tcp::socket m_socket;
	ConnectionManager& m_cm;
	std::array<char, BUFFSIZE> m_buffer;
	std::vector<boost::asio::const_buffer> m_write_buffer;
	void cm_stop();
public:
    ~Connection(){
		++x;
		std::cout << "Dtor Connection " << x << "\n";
	}
	Connection(const Connection&) = delete;
	Connection& operator=(const Connection&) = delete;
	explicit Connection(boost::asio::ip::tcp::socket socket, 
						ConnectionManager& manager);
	
	template <typename Result, typename Input>
	void start(std::function<Result(Input&)> fp){
		//do_read(fp);
		sync_read(fp);
	}

	void stop(){
		m_socket.close();
	}

	template<typename Result, typename Input>
	void sync_read(std::function<Result(Input&)> fp){
		auto self(shared_from_this());
		boost::system::error_code ec;
		auto bytes_transferred = m_socket.read_some(boost::asio::buffer(m_buffer), ec);
		
		std::cout << "Read something: " << bytes_transferred << " : " << ec.message() << "\n";
        if (!ec){
			std::cout << "No error in read ...\n";
		  std::string in("");
		  for(unsigned int i = 0; i < bytes_transferred; ++i){
			  in += m_buffer[i];
		  }
		  bool res = fp(in);
		  //bool res = test_func_bs22(in);
		  boost::asio::socket_base::send_buffer_size option(BUFFSIZE);
		  m_socket.set_option(option);
		  std::string out("");
		  if(res){
			  out = in + ": is palindrome";
		  }
		  else{
			  out = in + ": is NOT palindrome";
		  }
		  m_write_buffer.push_back(boost::asio::buffer(out));
		  //do_write();
		  m_buffer.empty();
		  sync_write(out);
        }
        else if (ec != boost::asio::error::operation_aborted){
          cm_stop();
        }
		
	}

	void sync_write(std::string& out){
		auto self(shared_from_this());
		auto bytes_written = boost::asio::write(m_socket, boost::asio::buffer(out, out.length()));
  
		if (bytes_written > 0){
			boost::system::error_code ignored_ec;
			m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
		}
		
		////if (ec != boost::asio::error::operation_aborted){
			cm_stop();
		////}
	}
/*
	template<typename Result, typename Input>
	void do_read(std::function<Result(Input&)> fp){std::cout << "Trying read\n";
		auto self(shared_from_this());
		m_socket.async_read_some(boost::asio::buffer(m_buffer),
		[this, self, fp](boost::system::error_code ec, std::size_t bytes_transferred){
        if (!ec){
		  std::string in("");
		  for(unsigned int i = 0; i < bytes_transferred; ++i){
			  in += m_buffer[i];
		  }
          ////buffer_.data(), bytes_transferred
		  ////do_read();if more data to read, based on indications from what was parsed so far.
		  // else replying now
		  
		  bool res = fp(in);
		  
		  boost::asio::socket_base::send_buffer_size option(BUFFSIZE);
		  m_socket.set_option(option);
		  std::string out("");
		  if(res){
			  out = in + ": is palindrome";
		  }
		  else{
			  out = in + ": is NOT palindrome";
		  }
		  m_write_buffer.push_back(boost::asio::buffer(out));
		  do_write();
		  m_buffer.empty();
        }
        else if (ec != boost::asio::error::operation_aborted){
          cm_stop();
        }
      });
	}
*/
/*
	void do_write(){
		auto self(shared_from_this());
		//boost::asio::write(m_socket, boost::asio::buffer(reply, reply.length()));
  
		boost::asio::async_write(m_socket, m_write_buffer,
		[this, self](boost::system::error_code ec, std::size_t){
			if (!ec){
				boost::system::error_code ignored_ec;
				m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
			}

			if (ec != boost::asio::error::operation_aborted){
				cm_stop();
			}
		});
	}
*/
};

using Connection_ptr = std::shared_ptr<Connection>;

#endif
