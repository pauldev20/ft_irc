/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:13:20 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/05 15:58:45 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <poll.h>		// poll
#include <map>			// std::map
#include <netinet/in.h>	// sockaddr_in
#include "Client.hpp"	// Client
#include "Channel.hpp"	// Channel

#define MAX_FDS 1000

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
		int 						port;
		std::string					password;
		int 						socketFd;
		struct sockaddr_in			address;
		std::vector<struct pollfd>	fds;
		std::map<int, Client*>		connectedClients;
		std::vector<Channel*>		channels;

		void						acceptNewConnection(int fd);
		void						recieveData(int fd);
};
