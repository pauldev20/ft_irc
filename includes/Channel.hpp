/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:02:45 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/08 11:23:28 by pgeeser          ###   ########.fr       */
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
		Channel(Client *oper, std::string const &channelName, std::string const &password = "");
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
        size_t  getUserLimit(void) const;

		void	setInviteOnly(bool inviteOnly);
        bool    isInviteOnly(void) const;

        void    setTopicRestriction(bool set);
        bool    isTopicRestriction(void) const;

		void	addInvited(Client *client);

		void	addClient(Client *client);
		void	removeClient(Client *client);
		void	removeClientFromAll(Client *client);
		std::string	getClientList(void);

		bool	isClientInChannel(Client *client);

		void	sendMessageToAll(std::string const &message);
		void	sendMessageToAllExcept(std::string const &message, Client *client);

        bool    checkChannelNameValidity(std::string const &channel_name);


		class AllreadyInChannelExcpetion: public std::exception
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
        bool                    topicRestriction; // @note needs to be true per default!
		std::vector<Client*>	clients;
		std::string				password;
		size_t					userLimit;
		bool					inviteOnly;
		std::vector<Client*>	invited;
		std::vector<Client*>	operators;
};
