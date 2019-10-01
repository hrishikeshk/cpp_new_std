#include <array>
#include <boost/asio.hpp>
#ifndef CONNECTION
#define CONNECTION

const unsigned int BUFFSIZE = 8192;
class ConnectionManager;

class Connection : public std::enable_shared_from_this<Connection>{
	void do_read();
	void do_write();
	boost::asio::ip::tcp::socket m_socket;
	ConnectionManager& m_cm;
	std::array<char, BUFFSIZE> m_buffer;
	std::vector<boost::asio::const_buffer> m_write_buffer;
	const std::string reply = "Hello World...";
public:
	Connection(const Connection&) = delete;
	Connection& operator=(const Connection&) = delete;
	explicit Connection(boost::asio::ip::tcp::socket socket,
      ConnectionManager& manager);
	void start();
	void stop();
	
};

using Connection_ptr = std::shared_ptr<Connection>;

#endif
