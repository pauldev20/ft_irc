/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:13:06 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/06 10:53:08 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <sys/socket.h>	// recv
#include <vector>		// std::vector

#define MAX_BUF_LENGTH 512

/* -------------------------------------------------------------------------- */
/*                                Class Methods                               */
/* -------------------------------------------------------------------------- */

Client::Client(int fd) : fd(fd), username(""), fullName(""), nickname(""), receiveBuffer(""), sendBuffer("") {
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
 * The function receive data from a client and handles exceptions for different scenarios.
 */
void	Client::receiveData(void) {
	std::vector<char> 	buffer(MAX_BUF_LENGTH);
	int ret = recv(this->fd, &buffer[0], buffer.size(), 0);
	std::string msg(buffer.begin(), buffer.end());
	if (ret == MAX_BUF_LENGTH) {
		throw MessageTooLongException();
	} else if (ret < 0) {
		this->receiveBuffer.clear();
		throw ConnectionErrorExcpetion();
	} else if (ret == 0) {
		this->receiveBuffer.clear();
		throw ConnectionClosedException();
	}
	msg.resize(ret); // resize to actual size (not MAX_BUF_LENGTH)
	this->receiveBuffer += msg;
	// std::cout << "[Client(" << this->fd << ") -> Server]: " << msg; //@todo debug print
}

/**
 * This function reads and returns a string from a receive buffer until it finds a "\r\n" sequence.
 * 
 * @return This function returns a string containing the data received by the client up until the first
 * occurrence of "\r\n" (carriage return and line feed). If "\r\n" is not found in the receive buffer,
 * an empty string is returned. The function also updates the receive buffer to remove the data that
 * has been returned.
 */
std::string	Client::readReceivedData(void) {
	std::string buffCpy = this->receiveBuffer;
	size_t crlfPos = buffCpy.find("\r\n");
	if (crlfPos == std::string::npos)
		return ("");
	this->receiveBuffer = buffCpy.substr(crlfPos + 2);
	std::cout << "[Client(" << this->fd << ") -> Server]: " << buffCpy.substr(0, crlfPos + 2);
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
	std::cout << "[Server -> Client(" << this->fd << ")]: " << this->sendBuffer;
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

void		Client::setUsername(std::string username) {
	this->username = username;
}

std::string	const &Client::getUsername(void) const {
	return (username);
}

void		Client::setFullName(std::string fullName) {
	this->fullName = fullName;
}

std::string	const &Client::getFullName(void) const {
	return (fullName);
}

void		Client::setNickname(std::string nickname) {
	this->nickname = nickname;
}

std::string	const &Client::getNickname(void) const {
	return (nickname);
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
