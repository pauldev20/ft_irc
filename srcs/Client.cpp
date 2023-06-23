/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:13:06 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/23 19:17:15 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <sys/socket.h>	// recv
#include <vector>		// std::vector

#define MAX_BUF_LENGTH 512

/* -------------------------------------------------------------------------- */
/*                                Class Methods                               */
/* -------------------------------------------------------------------------- */

Client::Client(int fd) : fd(fd), registered(false), authenticated(false), disconnected(false), username(""), fullName(""), nickname(""), receiveBuffer("") {
}

Client::~Client() {
}

/* -------------------------------------------------------------------------- */
/*                               Public Methods                               */
/* -------------------------------------------------------------------------- */

/**
 * The function receive data from a client and handles exceptions for
 * different scenarios.
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
	msg.resize(ret);
	this->receiveBuffer += msg;
}

/**
 * This function reads and returns a string from a receive buffer until
 * it finds a "\r\n" sequence.
 *
 * @return This function returns a string containing the data received by the
 * client up until the first occurrence of "\r\n" (carriage return and line feed). 
 * If "\r\n" is not found in the receive buffer, an empty string is returned.
 * The function also updates the receive buffer to remove the data that has been returned.
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
 * The function sends data from a client to a server and prints the sent 
 * data to the console.
 *
 * @return The function does not have a return type specified, so it does
 * not return anything.
 */
void		Client::sendData(std::string str) {
	int ret = send(this->fd, str.c_str(), str.length(), 0);
	if (ret < 0) {
		std::cout << "send error" << std::endl;
		return ;
	}
	std::cout << "[Server -> Client(" << this->fd << ")]: " << str;
}

/* -------------------------------------------------------------------------- */
/*                             Getters And Setters                            */
/* -------------------------------------------------------------------------- */

/**
 * The function returns the file descriptor of the client.
 * 
 * @return The `getFd` function is returning the value of the `fd`
 * member variable of the `Client` class.
 */
int			Client::getFd(void) const {
	return (fd);
}

/**
 * This function sets the disconnected status of a client.
 * 
 * @param disconnected A boolean variable that indicates whether the client is
 * disconnected or not. If the value is true, it means the client is disconnected,
 * and if the value is false, it means the client is still connected.
 * The function sets the value of this variable based on the input parameter.
 */
void		Client::setDisconnected(bool disconnected) {
	this->disconnected = disconnected;
}

/**
 * The function returns a boolean value indicating whether
 * the client is disconnected or not.
 * 
 * @return A boolean value indicating whether the client is disconnected or not.
 */
bool		Client::isDisconnected(void) const {
	return (disconnected);
}

/**
 * The function returns a boolean value indicating whether the
 * client is registered or not.
 * 
 * @return The function `isRegistered` is returning a boolean value,
 * which indicates whether the client is registered or not.
 * The value of `registered` is returned.
 */
bool		Client::isRegistered(void) const {
	return (registered);
}

/**
 * This function sets the "registered" boolean variable of a Client object.
 * 
 * @param registered "registered" is a boolean variable that represents whether a client is registered
 * or not. If "registered" is true, it means the client has completed the registration process, and if
 * it's false, it means the client has not yet registered. The function "setRegistered" sets the value
 * of this
 */
void		Client::setRegistered(bool registered) {
	this->registered = registered;
}

/**
 * The function returns a boolean value indicating whether the client is authenticated or not.
 * 
 * @return A boolean value indicating whether the client is authenticated or not.
 */
bool		Client::isAuthenticated(void) const {
	return (authenticated);
}

/**
 * This function sets the authentication status of a client.
 * 
 * @param authenticated "authenticated" is a boolean variable that
 * represents whether the client has been authenticated or not.
 * If it is set to true, it means that the client has been successfully authenticated,
 * and if it is set to false, it means that the client has not been authenticated or has
 * been logged out. The function
 */
void		Client::setAuthenticated(bool authenticated) {
	this->authenticated = authenticated;
}

/**
 * This function sets the username for a client object in C++.
 * 
 * @param username The parameter "username" is a string variable that
 * represents the username that we want to set for a client object.
 * The function "setUsername" takes this parameter and sets the username of
 * the client object to the value of the parameter.
 */
void		Client::setUsername(std::string username) {
	this->username = username;
}

/**
 * The function returns a constant reference to the username of a client object.
 * 
 * @return A constant reference to a string object representing the username of a client.
 */
std::string	const &Client::getUsername(void) const {
	return (username);
}

/**
 * This function sets the full name of a client object in C++.
 * 
 * @param fullName fullName is a parameter of type std::string that
 * represents the full name of a client. The function sets the value of
 * the fullName member variable of the Client class to the value
 * passed as the parameter.
 */
void		Client::setFullName(std::string fullName) {
	this->fullName = fullName;
}

/**
 * The function returns a constant reference to the full name of a client.
 * 
 * @return A constant reference to a `std::string`
 * object representing the full name of a `Client` object.
 */
std::string	const &Client::getFullName(void) const {
	return (fullName);
}

/**
 * This function sets the nickname of a client object in C++.
 * 
 * @param nickname The parameter "nickname" is a string that represents
 * the new nickname that the client wants to set. The function sets the
 * client's nickname to this new value.
 */
void		Client::setNickname(std::string nickname) {
	this->nickname = nickname;
}

/**
 * The function returns a constant reference to the nickname of a client object.
 * 
 * @return A constant reference to a string object representing the nickname of a client.
 */
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
