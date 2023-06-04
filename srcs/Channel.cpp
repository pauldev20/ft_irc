/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:02:41 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/04 21:33:58 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/* -------------------------------------------------------------------------- */
/*                                Class Methods                               */
/* -------------------------------------------------------------------------- */

Channel::Channel(Client *admin, std::string const &channelName) : name(channelName), topic("") {
	this->clients.push_back(admin);
}

Channel::~Channel() {
}

/* -------------------------------------------------------------------------- */
/*                             Getters and Setters                            */
/* -------------------------------------------------------------------------- */

/**
 * The function returns the name of a channel as a constant reference to a string.
 * 
 * @return A constant reference to a string object representing the name of the channel.
 */
std::string const &Channel::getName(void) const {
	return (this->name);
}

/**
 * This function sets the name of a channel object in C++.
 * 
 * @param name The parameter "name" is a constant reference to a string. It is used to set the name of
 * a channel object.
 */
void	Channel::setName(std::string const &name) {
	this->name = name;
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

/**
 * The function returns a pointer to the first client in the channel's client list, which is assumed to
 * be the admin.
 * 
 * @return A pointer to the first client in the `clients` array, which is assumed to be the admin
 * client.
 */
Client	*Channel::getAdmin(void) const {
	return (this->clients[0]);
}

/* -------------------------------------------------------------------------- */
/*                               Public Methods                               */
/* -------------------------------------------------------------------------- */

/**
 * The function adds a client to a channel while checking if the client has already been kicked or is
 * already in the channel.
 * 
 * @param client A pointer to a Client object that is being added to the Channel's list of clients.
 */
void	Channel::addClient(Client *client) {
	for (std::vector<Client*>::iterator it = this->kicked.begin(); it != this->kicked.end(); it++) {
		if (*it == client) {
			throw Channel::KickedClientExcpetion();
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

/**
 * The function removes a client from a channel and adds them to a list of kicked clients.
 * 
 * @param client The "client" parameter is a pointer to a Client object that represents the client to
 * be kicked from the channel.
 * 
 * @return nothing (void).
 */
void	Channel::kickClient(Client *client) {
	for (std::vector<Client*>::iterator it = this->clients.begin(); it != this->clients.end(); it++) {
		if (*it == client) {
			this->kicked.push_back(client);
			this->clients.erase(it);
			return ;
		}
	}
	throw Channel::CantBeKickedExcpetion();
}

/**
 * The function removes a client from the list of kicked clients in a channel.
 * 
 * @param client A pointer to a Client object that needs to be removed from the vector of kicked
 * clients in a Channel object.
 * 
 * @return nothing (void).
 */
void	Channel::unKickClient(Client *client) {
	for (std::vector<Client*>::iterator it = this->kicked.begin(); it != this->kicked.end(); it++) {
		if (*it == client) {
			this->kicked.erase(it);
			return ;
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
		(*it)->sendMessage(message);
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
		if (*it != client)
			(*it)->sendMessage(message);
	}
}

/* -------------------------------------------------------------------------- */
/*                                 Excpetions                                 */
/* -------------------------------------------------------------------------- */

const char *Channel::AllreadyInChannelExcpetion::what() const throw() {
	return ("Client is allready in channel");
}

const char *Channel::KickedClientExcpetion::what() const throw() {
	return ("Client is kicked and can't join channel");
}

const char *Channel::CantBeKickedExcpetion::what() const throw() {
	return ("Client can't be kicked from channel, since he is not part of it");
}
