/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 00:10:41 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/06 01:22:10 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

USER::USER(void) : Command(true, false) {
}

void USER::exec(Message& message, Server* server, Client* client) {
	(void)server;
	if (message.getParams().size() < 4) {
		client->addDataToBuffer(replies::ERR_NEEDMOREPARAMS("USER"));
		client->sendData();
		return ;
	}
	if (client->isRegistered() == true) {
		client->addDataToBuffer(replies::ERR_ALREADYREGISTRED());
		client->sendData();
		return ;
	}
	std::vector<std::string> params = message.getParams();
	client->setUsername(params[0]);
	client->setFullName(params[3]);
	// @todo check this in one function and combine with NICK command
	if (!client->getNickname().empty() && !client->getUsername().empty() && !client->getFullName().empty() && !client->isRegistered()) {
		client->setRegistered(true);
		client->addDataToBuffer(replies::RPL_WELCOME(client->getNickname(), ""));
		client->sendData();
	}
}