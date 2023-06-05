/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:13:06 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/05 19:15:24 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <sys/socket.h>	// recv
#include <vector>		// std::vector

#define MAX_BUF_LENGTH 512

/* -------------------------------------------------------------------------- */
/*                                Class Methods                               */
/* -------------------------------------------------------------------------- */

Client::Client(int fd) : fd(fd) {
	//@todo debug print
	// std::cout << "Client created" << std::endl;
}

Client::~Client() {
	//@todo debug print
	// std::cout << "Client destroyed" << std::endl;
}

/* -------------------------------------------------------------------------- */
/*                               Public Methods                               */
/* -------------------------------------------------------------------------- */

/**
 * The function receives data from a client and handles exceptions for different scenarios.
 */
void	Client::recieveData(void) {
	std::vector<char> 	buffer(MAX_BUF_LENGTH);
	int ret = recv(this->fd, &buffer[0], buffer.size(), 0);
	std::string msg(buffer.begin(), buffer.end());
	if (ret > 0) {
		this->recieveBuffer += msg;
		std::cout << "[Client(" << this->fd << ") -> Server]: " << msg;
	}
	if (ret == MAX_BUF_LENGTH) {
		this->recieveBuffer.clear();
		throw MessageTooLongException();
	} else if (ret < 0) {
		this->recieveBuffer.clear();
		throw ConnectionErrorExcpetion();
	} else if (ret == 0) {
		this->recieveBuffer.clear();
		throw ConnectionClosedException();
	}
}

/**
 * This function reads and returns a string from a receive buffer until it finds a "\r\n" sequence.
 * 
 * @return This function returns a string containing the data received by the client up until the first
 * occurrence of "\r\n" (carriage return and line feed). If "\r\n" is not found in the receive buffer,
 * an empty string is returned. The function also updates the receive buffer to remove the data that
 * has been returned.
 */
std::string	Client::readRecievedData(void) {
	std::string buffCpy = this->recieveBuffer;
	size_t crlfPos = buffCpy.find("\r\n");
	if (crlfPos == std::string::npos)
		return ("");
	this->recieveBuffer = buffCpy.substr(crlfPos + 2);
	return (buffCpy.substr(0, crlfPos + 2));
}

/**
 * This function adds a string of data to the send buffer of a client object.
 * 
 * @param data The parameter "data" is a string variable that represents the data that needs to be
 * added to the send buffer.
 */
void	Client::addDataToBuffer(std::string data) {
	this->sendBuffer += data;
}

/**
 * The function sends data from a client to a server and prints the sent data to the console.
 * 
 * @return The function does not have a return type specified, so it does not return anything.
 */
void		Client::sendData(void) {
	int ret = send(this->fd, this->sendBuffer.c_str(), this->sendBuffer.length(), 0);
	if (ret < 0) {
		std::cout << "send error" << std::endl;
		return ;
	} else
	std::cout << "[Server -> Client(" << this->fd << ")]: " << this->sendBuffer << std::endl;
	this->sendBuffer.clear();
}

/* -------------------------------------------------------------------------- */
/*                             Getters And Setters                            */
/* -------------------------------------------------------------------------- */

int			Client::getFd(void) const {
	return (fd);
}

bool		Client::isRegistered(void) const {
	return (registered);
}

void		Client::setRegistered(bool registered) {
	this->registered = registered;
}

bool		Client::isAuthenticated(void) const {
	return (authenticated);
}

void		Client::setAuthenticated(bool authenticated) {
	this->authenticated = authenticated;
}

/* -------------------------------------------------------------------------- */
/*                                 Exceptions                                 */
/* -------------------------------------------------------------------------- */

const char *Client::MessageTooLongException::what() const throw() {
	return ("Message too long");
}

const char *Client::ConnectionErrorExcpetion::what() const throw() {
	return ("Connection error");
}

const char *Client::ConnectionClosedException::what() const throw() {
	return ("Connection closed");
}
