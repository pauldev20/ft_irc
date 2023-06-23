/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 00:10:41 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/23 18:59:58 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

USER::USER(void) : Command(true, false) {
}

/**
 * This function sets the username and full name of a client and checks if
 * the client is already registered.
 * 
 * @param message The message object that contains the command and its
 * parameters sent by the client.
 * @param server A pointer to the Server object that the client is connected to.
 * @param client The "client" parameter is a pointer to the client
 * object that is executing the "USER" command.
 * 
 * @return If the number of parameters in the message is less than 3 or the
 * trailing message is empty, an error message is sent to the client and the
 * function returns. If the client is already registered, an error message is
 * sent to the client and the function returns. Otherwise, the username and
 * full name of the client are set and the function calls the `checkRegistered`
 * function.
 */
void USER::exec(Message& message, Server* server, Client* client) {
	(void)server;
	std::vector<std::string> params = message.getParams();
	if (params.size() < 3 || message.getTrailing().empty()) {
		client->sendData(replies::ERR_NEEDMOREPARAMS(client, "USER"));
		return ;
	}
	if (client->isRegistered() == true) {
		client->sendData(replies::ERR_ALREADYREGISTRED(client));
		return ;
	}
	client->setUsername(params[0]);
	client->setFullName(message.getTrailing());
	this->checkRegistered(client);
}
