/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:13:06 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/01 11:49:14 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <sys/socket.h>	// recv

Client::Client(int fd) : fd(fd) {
	std::cout << "Client created" << std::endl;
}

Client::~Client() {
	std::cout << "Client destroyed" << std::endl;
}

std::string	Client::recieveMessage(void) {
	static const int	bufferSize = 512;
	char				buffer[bufferSize];
	memset(buffer, 0, bufferSize);
	int ret = recv(this->fd, buffer, bufferSize, 0);
	std::string msg(buffer);
	if (msg.length() > 0)
		std::cout << "[Client -> Server]: " << msg;
	if (ret == bufferSize) {
		throw MessageTooLongException();
	} else if (ret < 0) {
		throw ConnectionErrorExcpetion();
	} else if (ret == 0) {
		throw ConnectionClosedException();
	}
	return (msg);
}

void		Client::sendMessage(std::string message) {
	int ret = send(this->fd, message.c_str(), message.length(), 0);
	if (ret < 0) {
		std::cout << "send error" << std::endl;
		return ;
	} else
	std::cout << "[Server -> Client]: " << message << std::endl;
}

int			Client::getFd(void) const {
	return (fd);
}

const char *Client::MessageTooLongException::what() const throw() {
	return ("Message too long");
}

const char *Client::ConnectionErrorExcpetion::what() const throw() {
	return ("Connection error");
}

const char *Client::ConnectionClosedException::what() const throw() {
	return ("Connection closed");
}
