/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:13:20 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/04 20:51:15 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>			// std::map
#include <netinet/in.h>	// sockaddr_in
#include "Client.hpp"	// Client
#include "Channel.hpp"	// Channel

class Server {
	public:
		Server(int port, std::string password);
		~Server();
		void 				start(void);
		void 				run(void);

		int					getPort(void) const;
		std::string const	&getPassword(void) const;

		void				addChannel(Channel *channel);
		void				removeChannel(Channel *channel);

	private:
		int 					port;
		std::string				password;
		int 					socketFd;
		struct sockaddr_in		address;
		fd_set					reads;
		fd_set					writes;
		std::map<int, Client*>	connectedClients;
		std::vector<Channel*>	channels;

		void						acceptNewConnection(int fd);
};