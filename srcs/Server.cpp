/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:12:48 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/04 21:28:30 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sys/socket.h> // socket, bind, listen, accept
#include <sys/select.h> // select
#include <fcntl.h>		// fcntl
#include <unistd.h>		// close
#include "Command.hpp"	// Command
#include "irc.hpp"

Server::Server(int port, std::string password) : port(port), password(password), socketFd(-1) {
	FD_ZERO(&(this->reads));
	FD_ZERO(&(this->writes));
	std::cout << "Server created" << std::endl;
}

Server::~Server() {
	std::map<int, Client*>::iterator it;
	for (it = this->connectedClients.begin(); it != this->connectedClients.end(); it++) 
		delete it->second;
	std::cout << "Server destroyed" << std::endl;
}

void Server::start() {
	std::cout << "Server started" << std::endl;

	// Creating socket file descriptor
	int fd = socket(AF_INET, SOCK_STREAM, 0);	// create socket -> AF_INET(Address Family Internet): IPv4, SOCK_STREAM: TCP
	fcntl(fd, F_SETFL, O_NONBLOCK);				// set socket to non-blocking -> will also work for the incoming connections since they will inherit that state from the listening socket.
	if (fd == -1)
	{
		std::cout << "Error: socket" << std::endl;
		return ;
	}
	this->socketFd = fd;

	//Allow socket descriptor to be reuseable
	int option = 1;
	setsockopt(this->socketFd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));	// set socket options -> SOL_SOCKET: socket level, SO_REUSEADDR: reuse address

	// Forcefully attaching socket to the port ('??')
	this->address.sin_family = AF_INET;			// AF_INET(Address Family Internet): IPv4
	this->address.sin_addr.s_addr = INADDR_ANY;	// INADDR_ANY: any address for binding
	this->address.sin_port = htons(this->port);	// htons(host to network short): convert a 16-bit quantity from the host byte order to the network byte order
	int res = bind(this->socketFd, (struct sockaddr*)&(this->address), sizeof(this->address));
	if (res == -1)
	{
		std::cout << "Error: bind" << std::endl;
		return ;
	}
	if (listen(this->socketFd, 3) < 0)
    {
        std::cout << "Error: listen" << std::endl;
		return ;
    }
	FD_SET(this->socketFd, &this->reads);
	std::cout << "Server listening on port " << this->port << std::endl;
}

void Server::run(void) {
	struct timeval timeout;
	timeout.tv_sec = 5;
	timeout.tv_usec = 500;
	fd_set testreads = this->reads;
	fd_set testwrites = this->writes;
	int res = select(1000, &testreads, &testwrites, NULL, &timeout);
	if (res == -1)
	{
		std::cout << "Error: select" << std::endl;
		return ;
	}
	else if (res == 0)
	{
		std::cout << "Timeout" << std::endl;
		return ;
	}

	for (int i = 0; i < 1000; i++)
    {
		if (FD_ISSET(i, &testreads)) {
			if (i == this->socketFd) {
				this->acceptNewConnection(i);

				// @todo remove this!!!
				if(!this->connectedClients.empty()) {
					Client *client = (--this->connectedClients.end())->second;
					client->sendMessage("Welcome to the IRC server");
					if (this->channels.empty())
						this->channels.push_back(new Channel(client, "default"));
					else {
						(*--this->channels.end())->addClient(client);
						(*--this->channels.end())->sendMessageToAll("New client has joined the channel!");
						(*--this->channels.end())->sendMessageToAllExcept("New client has joined the channel! (This message is only visible to other clients)", client);
					}
				}
			} else {
				try {
					std::string msg = this->connectedClients.find(i)->second->recieveMessage();
					msg += "\r\n";
					Command command;
					if (irc::parseMessage(command, msg) == ERROR) {
						std::cout << "Error: parseMessage" << std::endl;
						return ;
					}
					debug::debugCommand(command);
					if (irc::executeCommand(command, this, this->connectedClients.find(i)->second) == ERROR) {
						std::cout << "Error: executeCommand" << std::endl;
						return ;
					}
					// this->connectedClients.find(i)->second->sendMessage("Hello from server");
				} catch (const Client::ConnectionErrorExcpetion& e) {
					FD_CLR(i, &(this->reads));
					FD_CLR(i, &(this->writes));
					close(i);
					this->connectedClients.erase(i);
					std::cout << "recv error" << std::endl;
				} catch (const Client::ConnectionClosedException& e) {
					FD_CLR(i, &(this->reads));
					FD_CLR(i, &(this->writes));
					close(i);
					this->connectedClients.erase(i);
					std::cout << "[Server]: Connection closed" << std::endl;
				}
			}
		}
	}
}

void	Server::acceptNewConnection(int fd) {
	struct sockaddr_in	clientAddr;
	unsigned int		size = sizeof(clientAddr);
	int clientSockFd = accept(fd, (struct sockaddr*)&clientAddr, &size);
	if (clientSockFd < 0)
	{
		std::cout << "Error: accept" << std::endl;
		return ;
	}
	FD_SET(clientSockFd, &(this->reads));
	FD_SET(clientSockFd, &(this->writes));
	this->connectedClients[clientSockFd] = new Client(clientSockFd);
	std::cout << "[Server]: New connection established" << std::endl;
}
