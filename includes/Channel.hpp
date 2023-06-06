/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:02:45 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/06 11:20:46 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>		// std::vector
#include "Client.hpp"	// CanClient

/* -------------------------------------------------------------------------- */
/*                                   Classes                                  */
/* -------------------------------------------------------------------------- */

class Channel {
	public:
		Channel(Client *oper, std::string const &channelName);
		~Channel(void);

		size_t	getClientCount(void) const;

		std::string const &getName(void) const;

		std::string const &getTopic(void) const;
		void	setTopic(std::string const &topic);

		void	addOperator(Client *oper);
		void	removeOperator(Client *oper);
		bool	isOperator(Client *client) const;

		std::string const &getPassword(void) const;
		void	setPassword(std::string const &password);

		void	setUserLimit(int userLimit);

		void	setInviteOnly(bool inviteOnly);

		void	addInvited(Client *client);

		void	addClient(Client *client);
		void	removeClient(Client *client);

		bool	isClientInChannel(Client *client);

		void	kickClient(Client *client);
		void	unKickClient(Client *client);

		void	sendMessageToAll(std::string const &message);
		void	sendMessageToAllExcept(std::string const &message, Client *client);


		class AllreadyInChannelExcpetion: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class KickedClientExcpetion: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class CantBeKickedExcpetion: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class ChannelFullExcpetion: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class InviteOnlyExcpetion: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

	private:
		std::string				name;
		std::string				topic;
		std::vector<Client*>	clients;
		std::vector<Client*>	kicked;
		std::string				password;
		size_t					userLimit;
		bool					inviteOnly;
		std::vector<Client*>	invited;
		std::vector<Client*>	operators;
};