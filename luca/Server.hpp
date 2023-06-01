
#ifndef SERVER_HPP
#define SERVER_HPP

#include "Command.hpp"

#include <netinet/in.h> // sockaddr_in
#include <string>

class Server
{
	private:
		int					fd;
		struct sockaddr_in	address;
	public:
							Server();
							~Server();
		void				start(int port);
		int					acceptClient();
};

#endif