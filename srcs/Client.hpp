/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:13:15 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/01 11:48:39 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Client {
	public:
		Client(int fd);
		~Client();

		std::string	recieveMessage(void);
		void		sendMessage(std::string message);

		int getFd(void) const;

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
		int fd;
};
