/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:41:03 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/07 11:34:36 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Command.hpp"
#include "irc.hpp"

/* -------------------------------------------------------------------------- */
/*                                Class Methods                               */
/* -------------------------------------------------------------------------- */

Command::Command(bool needsPass, bool needsRegistration) : checkRegister(needsRegistration), checkPass(needsPass) {
}

Command::~Command() {
}

/* -------------------------------------------------------------------------- */
/*                               Public Methods                               */
/* -------------------------------------------------------------------------- */

/**
 * The function executes a command based on a message, server, and client, performing various checks
 * before executing.
 * 
 * @param message A reference to a Message object, which contains information about the command being
 * executed, including the command name and any parameters.
 * @param server A pointer to the Server object that the command is being executed on.
 * @param client The "client" parameter is a pointer to the client who sent the message that triggered
 * the execution of the command.
 * 
 * @return nothing (void). It is using the "return;" statement to exit the function early if certain
 * conditions are met.
 */
void	Command::execute(Message& message, Server* server, Client* client) {
	if (this->checkPass && !client->isAuthenticated()) {
		client->sendData(replies::ERR_PASSWDMISMATCH());
		return ;
	}
	if (this->checkRegister && !client->isRegistered()) {
		client->sendData(replies::ERR_NOTREGISTERED());
		return ;
	}
	if (message.getParams().size() < 1) {
		client->sendData(replies::ERR_NEEDMOREPARAMS(message.getCmdName()));
		return ;
	}
	this->exec(message, server, client);
}

/* -------------------------------------------------------------------------- */
/*                               Private Methods                              */
/* -------------------------------------------------------------------------- */

/**
 * The function checks if a client is registered and sends a welcome message if they are.
 * 
 * @param client The parameter "client" is a pointer to an object of the class "Client".
 * 
 * @return If any of the conditions in the if statement are true, the function will return without
 * doing anything.
 */
void	Command::checkRegistered(Client *client) const {
	if (client->getNickname().empty() || client->getUsername().empty() || client->getFullName().empty() || client->isRegistered())
		return ;
	client->setRegistered(true);
	client->sendData(replies::RPL_WELCOME(client->getNickname(), ""));
}
