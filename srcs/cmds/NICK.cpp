/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 23:17:01 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/06 01:20:45 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

NICK::NICK(void) : Command(true, false) {
}

void NICK::exec(Message& message, Server* server, Client* client) {
	(void)server;
	if (client->isRegistered() == true) {
		client->addDataToBuffer(replies::ERR_ALREADYREGISTRED());
		client->sendData();
		return ;
	}
	std::vector<std::string> params = message.getParams();
	// @todo check if nickname is valid (chars, length)
	if (params[0].empty()) {
		client->addDataToBuffer(replies::ERR_NONICKNAMEGIVEN());
		client->sendData();
		return ;
	}
	if (!server->checkNickname(params[0])) {
		client->addDataToBuffer(replies::ERR_NICKNAMEINUSE(params[0]));
		client->sendData();
		return ;
	}
	if (!client->getNickname().empty()) {
		client->addDataToBuffer(replies::RPL_NICKCHANGE(client->getNickname(), params[0], "")); // @todo add username??
	}
	client->setNickname(params[0]);
	// @todo check this in one function and combine with USER command
	if (!client->getNickname().empty() && !client->getNickname().empty() && !client->getFullName().empty() && !client->isRegistered()) {
		client->setRegistered(true);
		client->addDataToBuffer(replies::RPL_WELCOME(client->getNickname(), ""));
		client->sendData();
	}
}
