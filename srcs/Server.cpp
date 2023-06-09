/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:12:48 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/09 22:44:05 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <cstdlib>		// EXIT_FAILURE
#include <sys/socket.h> // socket, bind, listen, accept
#include <sys/select.h> // select
#include <fcntl.h>		// fcntl
#include <unistd.h>		// close
#include "Message.hpp"
#include "irc.hpp"

/* -------------------------------------------------------------------------- */
/*                                   Helpers                                  */
/* -------------------------------------------------------------------------- */

/**
 * The function creates and returns a struct pollfd with the specified file descriptor and events.
 *
 * @param fd The file descriptor for the file or socket being polled.
 * @param events The events parameter is a bitmask specifying the events the caller is interested in
 * for the file descriptor. It can be a combination of the following constants:
 *
 * @return A struct of type `pollfd` with the specified `fd`, `events`, and `revents` values.
 */
static struct pollfd	pollfd(int fd, short events) {
	struct pollfd pfd;
	pfd.fd = fd;
	pfd.events = events;
	pfd.revents = 0;
	return (pfd);
}

/**
 * The function removes a specific element from a vector of pollfd structures based on its file
 * descriptor.
 *
 * @param vector A reference to a vector of struct pollfd elements.
 * @param element The element parameter is a struct pollfd variable that represents the poll file
 * descriptor to be removed from the vector. The function iterates through the vector and removes the
 * element with the same file descriptor as the one passed in.
 */
static void				removePollfdFromVector(std::vector<struct pollfd> &vector, int fd) {
	std::vector<struct pollfd>::iterator it;
	for (it = vector.begin(); it != vector.end(); it++) {
		if ((*it).fd == fd) {
			vector.erase(it);
			break ;	
		}
	}
}

static void				printError(std::string message, bool fatal = false) {
	std::cerr << "\033[31mError\033[0m: " << message << std::endl;
	if (fatal)
		throw EXIT_FAILURE;
}

/* -------------------------------------------------------------------------- */
/*                                Class Methods                               */
/* -------------------------------------------------------------------------- */

Server::Server(int port, std::string password) : port(port), password(password), socketFd(-1) {
	this->fds.reserve(MAX_FDS);
}

Server::~Server() {
	std::map<int, Client*>::iterator it;
	for (it = this->connectedClients.begin(); it != this->connectedClients.end(); it++)
		delete it->second;
}

/* -------------------------------------------------------------------------- */
/*                             Getters And Setters                            */
/* -------------------------------------------------------------------------- */

/**
 * The function returns the port number of the server.
 *
 * @return The `getPort` function is returning the value of the `port` member variable of the `Server`
 * class.
 */
int		Server::getPort(void) const {
	return (this->port);
}

/**
 * The function returns a constant reference to the password of a server object.
 *
 * @return A constant reference to a string object representing the password of the server.
 */
std::string	const &Server::getPassword(void) const {
	return (this->password);
}

/**
 * The function adds a channel to a vector of channels in a server object.
 *
 * @param channel The parameter "channel" is a pointer to an object of the class "Channel". The
 * function "addChannel" takes this pointer as an argument and adds it to a vector of Channel pointers
 * called "channels" that belongs to the Server class.
 */
void	Server::addChannel(Channel *channel) {
	this->channels.push_back(channel);
}

/**
 * The function removes a given channel from a vector of channels in a server.
 *
 * @param channel A pointer to a Channel object that needs to be removed from the vector of channels in
 * the Server class.
 *
 * @return nothing (void).
 */
void	Server::removeChannel(Channel *channel) {
	std::vector<Channel*>::iterator it;
	for (it = this->channels.begin(); it != this->channels.end(); it++) {
		if (*it == channel) {
			this->channels.erase(it);
			return ;
		}
	}
}

Channel	*Server::getChannelByName(std::string const &name) {
	std::vector<Channel*>::iterator it;
	for (it = this->channels.begin(); it != this->channels.end(); it++) {
		if ((*it)->getName() == name)
			return (*it);
	}
	return (NULL);
}

std::vector<Channel*>	&Server::getChannels(void) {
	return (this->channels);
}

/* -------------------------------------------------------------------------- */
/*                               Public Methods                               */
/* -------------------------------------------------------------------------- */

/**
 * The function starts a server by creating a socket, setting it to non-blocking, and binding it to a
 * port.
 *
 * @return The function does not have a return type, so it does not return anything. However, it may
 * exit early and not execute the rest of the code if there are errors in creating the socket, setting
 * socket options, binding the socket, or listening to the socket.
 */
void Server::start() {
	// Creating socket file descriptor
	int fd = socket(AF_INET, SOCK_STREAM, 0);	// create socket -> AF_INET(Address Family Internet): IPv4, SOCK_STREAM: TCP
	if (fd < 0)
		printError("socket", true);
	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)		// set socket to non-blocking -> will also work for the incoming connections since they will inherit that state from the listening socket.
		printError("fcntl", true);
	this->socketFd = fd;

	//Allow socket descriptor to be reuseable
	int option = 1;
	if (setsockopt(this->socketFd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) < 0)	// set socket options -> SOL_SOCKET: socket level, SO_REUSEADDR: reuse address
		printError("setsockopt", true);

	// Forcefully attaching socket to the port ('??')
	this->address.sin_family = AF_INET;			// AF_INET(Address Family Internet): IPv4
	this->address.sin_addr.s_addr = INADDR_ANY;	// INADDR_ANY: any address for binding
	this->address.sin_port = htons(this->port);	// htons(host to network short): convert a 16-bit quantity from the host byte order to the network byte order
	int res = bind(this->socketFd, (struct sockaddr*)&(this->address), sizeof(this->address));
	if (res == -1)
		printError("bind", true);
	if (listen(this->socketFd, 3) < 0)
		printError("listen", true);
	this->fds.push_back(pollfd(this->socketFd, POLLIN));
}

/**
 * This function runs the server and handles incoming connections and messages from clients.
 *
 * @return The function does not have a return type, so it does not return anything. However, it does
 * have several return statements that are used to exit the function early in case of errors or
 * timeouts.
 */
void Server::run(void) {
	int res = poll(&this->fds[0], this->fds.size(), 5000);
	if (res == -1)
		return (printError("poll"));
	else if (res == 0)
		return ;

	for (size_t i = 0; i < this->fds.size(); i++)
    {
		if (this->fds[i].revents & POLLIN) {
			if (this->fds[i].fd == this->socketFd) {
				this->acceptNewConnection(this->fds[i].fd);
			} else {
				this->receiveData(this->fds[i].fd);
			}
		}
	}
}

bool	Server::checkNickname(std::string const &nickname) {
	std::map<int, Client*>::iterator it;
	for (it = this->connectedClients.begin(); it != this->connectedClients.end(); it++) {
		if (it->second->getNickname() == nickname)
			return (false);
	}
	return (true);
}

Client	*Server::getClientByNickname(std::string const &nickname) {
	std::map<int, Client*>::iterator it;
	for (it = this->connectedClients.begin(); it != this->connectedClients.end(); it++) {
		if (it->second->getNickname() == nickname)
			return (it->second);
	}
	return (NULL);
}

/* -------------------------------------------------------------------------- */
/*                               Private Methods                              */
/* -------------------------------------------------------------------------- */

/**
 * The function accepts a new client connection and adds it to the list of connected clients.
 *
 * @param fd fd is the file descriptor of the server socket that is listening for incoming connections.
 *
 * @return The function does not have a return type, so nothing is being returned.
 */
void	Server::acceptNewConnection(int fd) {
	struct sockaddr_in	clientAddr;
	unsigned int		size = sizeof(clientAddr);
	int clientSockFd = accept(fd, (struct sockaddr*)&clientAddr, &size);
	if (clientSockFd == -1)
		return (printError("accept"));
	this->fds.push_back(pollfd(clientSockFd, POLLIN));
	this->connectedClients[clientSockFd] = new Client(clientSockFd);
	std::cout << "[Server]: New connection established" << std::endl;
}

/**
 * This function receives data from a client and executes commands based on the received messages.
 *
 * @param fd The parameter `fd` is an integer representing the file descriptor of the client socket
 * that the server is currently receiving data from.
 *
 * @return The function does not have a return type, so it does not return anything.
 */
void	Server::receiveData(int fd) {
	try {
		this->connectedClients.find(fd)->second->receiveData();
		while (true) {
			Client *client = this->connectedClients.find(fd)->second;
			std::string msg = client->readReceivedData();
			if (msg.empty())
				break ;
			Message message;
			if (irc::parse_message(message, msg) == ERROR) {
				printError("parse_message");
				continue ;
			}
			// debug::print_message(message);
			if (irc::execute_message(message, this, client) == ERROR) {
				printError("executeMessage");
				continue ;
			}
			if (client->isDisconnected())
				throw Client::ConnectionClosedException();
		}
	} catch (const Client::ConnectionErrorExcpetion& e) {
		close(fd);
		Client *client = this->connectedClients.find(fd)->second;
		for (std::vector<Channel*>::iterator it = this->channels.begin(); it != this->channels.end(); it++) {
			if ((*it)->isClientInChannel(client)) {
				(*it)->sendMessageToAllExcept(replies::RPL_QUIT(client, "Unexpected error"), client);
				(*it)->removeClientFromAll(this->connectedClients.find(fd)->second);
			}
		}
		this->connectedClients.erase(fd);
		removePollfdFromVector(this->fds, fd);
		std::cout << "[Server]: Connection receive error" << std::endl;
	} catch (const Client::ConnectionClosedException& e) {
		close(fd);
		Client *client = this->connectedClients.find(fd)->second;
		for (std::vector<Channel*>::iterator it = this->channels.begin(); it != this->channels.end(); it++) {
			if ((*it)->isClientInChannel(client)) {
				if (!client->isDisconnected())
					(*it)->sendMessageToAllExcept(replies::RPL_QUIT(client, "Unexpected EOF"), client);
				(*it)->removeClientFromAll(this->connectedClients.find(fd)->second);
			}
		}
		this->connectedClients.erase(fd);
		removePollfdFromVector(this->fds, fd);
		std::cout << "[Server]: Connection closed" << std::endl;
	} catch (const Client::MessageTooLongException& e) {
		std::cout << "[Server]: Message received was too long" << std::endl;
	}
}
