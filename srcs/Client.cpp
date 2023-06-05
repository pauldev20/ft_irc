/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:13:06 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/05 18:43:07 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <sys/socket.h>	// recv

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
	static const int	bufferSize = 512;
	char				buffer[bufferSize];
	// memset(buffer, 0, bufferSize); //@todo idk if allowed?
	int ret = recv(this->fd, buffer, bufferSize, 0);
	std::string msg(buffer);
	if (msg.length() > 0)
		std::cout << "[Client(" << this->fd << ") -> Server]: " << msg;
	if (ret == bufferSize) {
		this->recieveBuffer.clear();
		throw MessageTooLongException();
	} else if (ret < 0) {
		this->recieveBuffer.clear();
		throw ConnectionErrorExcpetion();
	} else if (ret == 0) {
		this->recieveBuffer.clear();
		throw ConnectionClosedException();
	}
	this->recieveBuffer += msg;
}

/**
 * The function reads and returns the received data from a client, clearing the receive buffer if a
 * complete message is found.
 * 
 * @return If the `recieveBuffer` contains a complete message (i.e. ends with "\r\n"), then the
 * function returns the message as a `std::string` and clears the `recieveBuffer`. If the
 * `recieveBuffer` does not contain a complete message, then an empty string is returned.
 */
std::string	Client::readRecievedData(void) {
	std::string msg = this->recieveBuffer;
	if (msg.length() > 0 && msg.find("\r\n") != std::string::npos)
		this->recieveBuffer.clear();
	else
		return ("");
	return (msg);
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
 * This function sends a message from the server to a client and prints it to the console.
 * 
 * @return The function does not have a return type specified, so it does not return anything.
 */
void		Client::sendMessage(void) {
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
