/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:02:41 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/23 19:15:17 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <algorithm>	// std::find

/* -------------------------------------------------------------------------- */
/*                                Class Methods                               */
/* -------------------------------------------------------------------------- */

Channel::Channel(Client *oper, std::string const &channelName, std::string const &password)
	: name(channelName), topic(""), topicRestriction(false), password(password), userLimit(0), inviteOnly(false) {
	this->clients.push_back(oper);
    this->operators.push_back(oper);
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
 * @param topic The parameter "topic" is a constant reference to a string.
 * It is used to set the topic of a channel object.
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

/**
 * This function removes a given client from a vector of operators in a channel.
 * 
 * @param oper oper is a pointer to a Client object that represents the operator
 * being removed from the Channel's list of operators.
 * 
 * @return nothing (void).
 */
void	Channel::removeOperator(Client *oper) {
	for (std::vector<Client*>::iterator it = this->operators.begin(); it != this->operators.end(); it++) {
		if (*it == oper) {
			this->operators.erase(it);
			return ;
		}
	}
}

/**
 * This function checks if a given client is an operator of a channel.
 * 
 * @param client The "client" parameter is a pointer to an object of the
 * "Client" class, which represents a user connected to the IRC server.
 * The "isOperator" function is a member function of the "Channel" class, and it
 * checks whether the given client is an operator.
 * 
 * @return A boolean value indicating whether the given client is an operator
 * in the channel or not.
 */
bool	Channel::isOperator(Client *client) const {
	return (std::find(this->operators.begin(), this->operators.end(), client) != this->operators.end());
}

/**
 * This function returns a reference to a vector of pointers to Client objects
 * representing the operators of a channel.
 * 
 * @return A reference to a `std::vector` of pointers to `Client` objects,
 * which represents the list of operators for the `Channel` object.
 */
std::vector<Client*> &Channel::getOperators(void) {
	return (this->operators);
}

/**
 * This function returns a constant reference to the password of a channel.
 * 
 * @return A constant reference to the password string of the Channel object.
 */
std::string const &Channel::getPassword(void) const {
	return (this->password);
}

/**
 * This function sets the password for a channel object.
 * 
 * @param password The parameter `password` is a constant reference
 * to a `std::string` object. It is used to set the password of a `Channel` object.
 */
void	Channel::setPassword(std::string const &password) {
	this->password = password;
}

/**
 * This function sets the user limit for a channel.
 * 
 * @param userLimit userLimit is an integer parameter that represents the
 * maximum number of users allowed in a channel. This function sets the user
 * limit of the channel to the specified value.
 */
void	Channel::setUserLimit(int userLimit) {
	this->userLimit = userLimit;
}

/**
 * This function sets the inviteOnly flag of a Channel object in C++.
 * 
 * @param inviteOnly A boolean variable that indicates whether the channel is
 * invite-only or not. If it is set to true, only users who have been invited
 * by a channel operator can join the channel. If it is set to false, anyone
 * can join the channel without an invitation. The function sets the value of
 * the invite
 */
void	Channel::setInviteOnly(bool inviteOnly) {
	this->inviteOnly = inviteOnly;
}

/**
 * The function returns a boolean value indicating whether the channel
 * is invite-only or not.
 * 
 * @return The function `isInviteOnly` is returning a boolean value
 * that indicates whether the channel is invite-only or not. The value
 * returned is the value of the `inviteOnly` member variable of the `Channel` class.
 */
bool    Channel::isInviteOnly(void) const {
    return (this->inviteOnly);
}

/**
 * The function returns the user limit of a channel.
 * 
 * @return The function `getUserLimit` is returning the value of the
 * `userLimit` member variable of the `Channel` class. The return type
 * of the function is `size_t`, which is an unsigned integer type used
 * for representing sizes and counts.
 */
size_t  Channel::getUserLimit(void) const {
    return (this->userLimit);
}

/* -------------------------------------------------------------------------- */
/*                               Public Methods                               */
/* -------------------------------------------------------------------------- */

/**
 * This function adds a client to a vector of invited clients for a channel,
 * if they are not already in the vector.
 * 
 * @param client A pointer to a Client object that is being added to
 * the vector of invited clients in a Channel object.
 * 
 * @return If the client is already in the list of invited clients,
 * the function returns without doing anything. If the client is not in
 * the list, it is added to the list of invited clients. No value is explicitly
 * returned by the function.
 */
void	Channel::addInvited(Client *client) {
	for (std::vector<Client*>::iterator it = this->invited.begin(); it != this->invited.end(); it++) {
		if (*it == client) {
			return ;
		}
	}
	this->invited.push_back(client);
}

/**
 * The function adds a client to a channel while checking if the client has
 * already been kicked or is already in the channel.
 *
 * @param client A pointer to a Client object that is being added to the
 * Channel's list of clients.
 */
void	Channel::addClient(Client *client) {
	if (this->userLimit > 0 && this->clients.size() >= this->userLimit) {
		throw Channel::ChannelFullExcpetion();
	}
	if (this->inviteOnly && std::find(this->invited.begin(), this->invited.end(), client) == this->invited.end()) {
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
 * @param client The parameter "client" is a pointer to an object of the class
 * "Client". It is used in the function "removeClient" of the class "Channel"
 * to remove a specific client from the vector of clients stored in the channel object.
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

/**
 * The function removes a given client from all the client lists in a channel.
 * 
 * @param client A pointer to a Client object that needs to be removed from
 * all the vectors (clients, invited, and operators) in the Channel object.
 */
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
 * The function returns a reference to a vector of pointers to Client objects
 * stored in a Channel object.
 * 
 * @return A reference to a vector of pointers to Client objects, which is
 * a member variable of the Channel class.
 */
std::vector<Client*> &Channel::getClients(void) {
	return (this->clients);
}

/**
 * The function sends a message to all clients in a channel.
 *
 * @param message A constant reference to a string object that represents the
 * message to be sent to all clients in the channel.
 */
void	Channel::sendMessageToAll(std::string const &message) {
	for (std::vector<Client*>::iterator it = this->clients.begin(); it != this->clients.end(); it++) {
		(*it)->sendData(message);
	}
}

/**
 * This function sends a message to all clients in a channel except for a
 * specified client.
 *
 * @param message A string containing the message to be sent to all clients
 * in the channel except for the specified client.
 * @param client The "client" parameter is a pointer to a Client object.
 * It is used to identify the client who should not receive the message being
 * sent to all other clients in the channel.
 */
void	Channel::sendMessageToAllExcept(std::string const &message, Client *client) {
	for (std::vector<Client*>::iterator it = this->clients.begin(); it != this->clients.end(); it++) {
		if (*it != client) {
			(*it)->sendData(message);
		}
	}
}

/**
 * The function checks if a given client is present in a channel by iterating
 * through a vector of clients.
 * 
 * @param client The parameter "client" is a pointer to an object of the
 * class "Client".
 * 
 * @return This function is checking if a given client is present in
 * the channel's list of clients and returns a boolean value of true if the
 * client is found, and false otherwise.
 */
bool	Channel::isClientInChannel(Client *client) {
	for (std::vector<Client*>::iterator it = this->clients.begin(); it != this->clients.end(); it++) {
		if (*it == client) {
			return (true);
		}
	}
	return (false);
}

/**
 * This function checks if a given channel name is valid by verifying if it
 * starts with '#' or '&'.
 * 
 * @param channel_name The parameter `channel_name` is a constant reference
 * to a string, which represents the name of a channel.
 * 
 * @return A boolean value is being returned. It will be true if the first
 * character of the input string is '#' or '&', and false otherwise.
 */
bool    Channel::checkChannelNameValidity(std::string const &channel_name) {
    if (channel_name[0] != '#' && channel_name[0] != '&') {
        return (false);
    }
    return (true);
}

/**
 * The function returns a boolean value indicating whether the channel has a
 * topic restriction or not.
 * 
 * @return A boolean value indicating whether the channel has a topic
 * restriction or not.
 */
bool    Channel::isTopicRestriction(void) const {
    return (this->topicRestriction);
}

/**
 * This function sets the topic restriction flag for a channel.
 * 
 * @param set The "set" parameter is a boolean value that determines
 * whether the topic restriction should be set or not. If "set" is true, it
 * means that the topic restriction is enabled, and if it is false, it means
 * that the topic restriction is disabled.
 */
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
