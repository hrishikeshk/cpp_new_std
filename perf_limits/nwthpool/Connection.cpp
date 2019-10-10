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

bool test_func_bs22(std::string& a){
	int i = 0, j = a.length() - 1;
	while(i < 100000){
		++i;
		j = 0;
		while(j < i){
			j++;
		}
	}
	i = 0;
	j = a.length() - 1;
	while(i < j){
		if(a[i] != a[j]){
			std::cout << "Is Palindrome: " << a << " = " << false << "\n";
			return false;
		}
		++i;
		--j;
	}
	std::cout << "Is Palindrome: " << a << " = " << true << "\n";
	return true;
}
