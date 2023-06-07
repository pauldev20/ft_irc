/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:02:41 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/07 11:22:03 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/* -------------------------------------------------------------------------- */
/*                                Class Methods                               */
/* -------------------------------------------------------------------------- */

Channel::Channel(Client *oper, std::string const &channelName) : name(channelName), topic(""), password(""), userLimit(0), inviteOnly(false) {
	this->clients.push_back(oper);
}

Channel::~Channel() {
}

/* -------------------------------------------------------------------------- */
/*                             Getters and Setters                            */
/* -------------------------------------------------------------------------- */

/**
 * The function returns the number of clients in a channel.
 *
 * @return The number of clients in a channel.
 */
size_t	Channel::getClientCount(void) const {
	return (this->clients.size());
}

/**
 * The function returns the name of a channel as a constant reference to a string.
 *
 * @return A constant reference to a string object representing the name of the channel.
 */
std::string const &Channel::getName(void) const {
	return (this->name);
}

/**
 * The function returns a constant reference to the topic of a channel.
 *
 * @return A constant reference to a string object representing the topic of the channel.
 */
std::string const &Channel::getTopic(void) const {
	return (this->topic);
}

/**
 * This function sets the topic of a channel in C++.
 *
 * @param topic The parameter "topic" is a constant reference to a string. It is used to set the topic
 * of a channel object.
 */
void	Channel::setTopic(std::string const &topic) {
	this->topic = topic;
}

void	Channel::addOperator(Client *oper) {
	for (std::vector<Client*>::iterator it = this->operators.begin(); it != this->operators.end(); it++) {
		if (*it == oper) {
			return ;
		}
	}
	for (std::vector<Client*>::iterator it = this->clients.begin(); it != this->clients.end(); it++) {
		if (*it == oper) {
			this->operators.push_back(oper);
			return ;
		}
	}
}

void	Channel::removeOperator(Client *oper) {
	for (std::vector<Client*>::iterator it = this->operators.begin(); it != this->operators.end(); it++) {
		if (*it == oper) {
			this->operators.erase(it);
			return ;
		}
	}
}

bool	Channel::isOperator(Client *client) const {
	return (std::find(this->operators.begin(), this->operators.end(), client) != this->operators.end());
}

std::string const &Channel::getPassword(void) const {
	return (this->password);
}

void	Channel::setPassword(std::string const &password) {
	this->password = password;
}

void	Channel::setUserLimit(int userLimit) {
	this->userLimit = userLimit;
}

void	Channel::setInviteOnly(bool inviteOnly) {
	this->inviteOnly = inviteOnly;
}

bool    Channel::isInviteOnly(void) const {
    return (this->inviteOnly);
}

/* -------------------------------------------------------------------------- */
/*                               Public Methods                               */
/* -------------------------------------------------------------------------- */

void	Channel::addInvited(Client *client) {
	this->invited.push_back(client);
}

/**
 * The function adds a client to a channel while checking if the client has already been kicked or is
 * already in the channel.
 *
 * @param client A pointer to a Client object that is being added to the Channel's list of clients.
 */
void	Channel::addClient(Client *client) {
	if (this->userLimit > 0 && this->clients.size() >= this->userLimit) {
		throw Channel::ChannelFullExcpetion();
	}
	if (this->inviteOnly && std::find(this->clients.begin(), this->clients.end(), client) == this->clients.end()) {
		throw Channel::InviteOnlyExcpetion();
	}
	for (std::vector<Client*>::iterator it = this->invited.begin(); it != this->invited.end(); it++) {
		if (*it == client) {
			this->invited.erase(it);
			break ;
		}
	}
	for (std::vector<Client*>::iterator it = this->clients.begin(); it != this->clients.end(); it++) {
		if (*it == client) {
			throw Channel::AllreadyInChannelExcpetion();
		}
	}
	this->clients.push_back(client);
}

/**
 * This function removes a client from a vector of clients in a channel.
 *
 * @param client The parameter "client" is a pointer to an object of the class "Client". It is used in
 * the function "removeClient" of the class "Channel" to remove a specific client from the vector of
 * clients stored in the channel object.
 *
 * @return nothing (void).
 */
void	Channel::removeClient(Client *client) {
	for (std::vector<Client*>::iterator it = this->clients.begin(); it != this->clients.end(); it++) {
		if (*it == client) {
			this->clients.erase(it);
			return ;
		}
	}
}

void	Channel::removeClientFromAll(Client *client) {
	for (std::vector<Client*>::iterator it = this->clients.begin(); it != this->clients.end(); it++) {
		if (*it == client) {
			this->clients.erase(it);
			break ;
		}
	}
	for (std::vector<Client*>::iterator it = this->invited.begin(); it != this->invited.end(); it++) {
		if (*it == client) {
			this->invited.erase(it);
			break ;
		}
	}
	for (std::vector<Client*>::iterator it = this->operators.begin(); it != this->operators.end(); it++) {
		if (*it == client) {
			this->operators.erase(it);
			break ;
		}
	}
}

/**
 * The function sends a message to all clients in a channel.
 *
 * @param message A constant reference to a string object that represents the message to be sent to all
 * clients in the channel.
 */
void	Channel::sendMessageToAll(std::string const &message) {
	for (std::vector<Client*>::iterator it = this->clients.begin(); it != this->clients.end(); it++) {
		(*it)->sendData(message);
	}
}

/**
 * This function sends a message to all clients in a channel except for a specified client.
 *
 * @param message A string containing the message to be sent to all clients in the channel except for
 * the specified client.
 * @param client The "client" parameter is a pointer to a Client object. It is used to identify the
 * client who should not receive the message being sent to all other clients in the channel.
 */
void	Channel::sendMessageToAllExcept(std::string const &message, Client *client) {
	for (std::vector<Client*>::iterator it = this->clients.begin(); it != this->clients.end(); it++) {
		if (*it != client) {
			(*it)->sendData(message);
		}
	}
}

bool	Channel::isClientInChannel(Client *client) {
	for (std::vector<Client*>::iterator it = this->clients.begin(); it != this->clients.end(); it++) {
		if (*it == client) {
			return (true);
		}
	}
	return (false);
}

bool    Channel::checkChannelNameValidity(std::string const &channel_name) {
    if (channel_name[0] != '#' && channel_name[0] != '&') {
        return (false);
    }
    return (true);
}

bool    Channel::isTopicRestriction(void) const {
    return (this->topicRestriction);
}

void    Channel::setTopicRestriction(bool set) {
    this->topicRestriction = set;
}

/* -------------------------------------------------------------------------- */
/*                                 Excpetions                                 */
/* -------------------------------------------------------------------------- */

const char *Channel::AllreadyInChannelExcpetion::what() const throw() {
	return ("Client is allready in channel");
}

const char *Channel::ChannelFullExcpetion::what() const throw() {
	return ("Channel is full");
}

const char *Channel::InviteOnlyExcpetion::what() const throw() {
	return ("Channel is invite only");
}
