/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:13:15 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/05 18:35:10 by pgeeser          ###   ########.fr       */
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

		// recieve data
		void		recieveData(void);
		std::string	readRecievedData(void);

		// send data
		void		addDataToBuffer(std::string data);
		void		sendMessage(void);

		int getFd(void) const;

		bool isRegistered(void) const;
		void setRegistered(bool registered);

		bool isAuthenticated(void) const;
		void setAuthenticated(bool authenticated);

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
		std::string	recieveBuffer;
		std::string	sendBuffer;
};
