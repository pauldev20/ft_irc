
#include "Server.hpp"

#include <netinet/in.h> // sockaddr_in
#include <sys/socket.h> // socket
#include <iostream> // perror
#include <fcntl.h> // fcntl
// #include <arpa/inet.h> // htons

Server::Server()
{
}

Server::~Server()
{
}

void	Server::start(int port)
{
	int	temp = 0;
	int	enable = 1;

	this->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->fd == 0)
	{
		perror("socket failed");
		return ;
	}
	if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(enable)))
		perror("setsockopt");
	// if (fcntl(this->fd, F_SETFL, O_NONBLOCK) < 0)
	// 	perror("fcntl");
	this->address.sin_family = AF_INET;
	this->address.sin_addr.s_addr = INADDR_ANY;
	this->address.sin_port = htons(port); // @note what is this?
	temp = bind(this->fd, (struct sockaddr *)&this->address, sizeof(this->address));
	if (temp < 0)
	{
		perror("bind failed");
		return ;
	}
	temp = listen(this->fd, 3);
	if (temp < 0)
	{
		perror("listen failed");
		return ;
	}
	std::cout << "Server started on port " << port << std::endl;
}

// @note create a client class
int	Server::acceptClient()
{
	int client_fd = 0;
	int addrlen = sizeof(this->address);

	std::cout << "Waiting for a connection..." << std::endl;
	client_fd = accept(this->fd, (struct sockaddr *)&this->address, (socklen_t*)&addrlen);
	if (client_fd < 0)
	{
		perror("accept failed");
		return (-1);
	}
	// if (fcntl(client_fd, F_SETFL, O_NONBLOCK) < 0)
	// 	perror("fcntl");
	const char *hello = "Hello from server";
	send(client_fd, hello, strlen(hello), 0 );
	std::cout << "Hello message sent" << std::endl;
	return (client_fd);
}