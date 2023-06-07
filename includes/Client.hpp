/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:13:15 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/07 10:51:07 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

/* -------------------------------------------------------------------------- */
/*                                   Classes                                  */
/* -------------------------------------------------------------------------- */

class Client {
	public:
		Client(int fd);
		~Client();

		// receive data
		void		receiveData(void);
		std::string	readReceivedData(void);

		// send data
		void		sendData(std::string str);

		int getFd(void) const;

		void setDisconnected(bool disconnected);

		bool isRegistered(void) const;
		void setRegistered(bool registered);

		bool isAuthenticated(void) const;
		void setAuthenticated(bool authenticated);

		void setUsername(std::string name);
		std::string const &getUsername(void) const;

		void setFullName(std::string fullName);
		std::string const &getFullName(void) const;

		void setNickname(std::string nickname);
		std::string const &getNickname(void) const;

		class MessageTooLongException: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class ConnectionErrorExcpetion: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class ConnectionClosedException: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

	private:
		int			fd;
		bool		registered;
		bool		authenticated;
		bool		disconnected;
		std::string	username;
		std::string	fullName;
		std::string	nickname;
		std::string	receiveBuffer;
};
