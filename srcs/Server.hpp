/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:13:20 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/01 11:23:06 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <iostream>
#include <netinet/in.h>	// sockaddr_in
#include "Client.hpp"	// Client

class Server {
	public:
		Server(int port, std::string password);
		~Server();
		void start(void);
		void run(void);

	private:
		int 					port;
		std::string				password;
		int 					socketFd;
		struct sockaddr_in		address;
		fd_set					reads;
		fd_set					writes;
		std::map<int, Client*>	connectedClients;

		void						acceptNewConnection(int fd);
};