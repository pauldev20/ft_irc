/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 23:17:01 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/07 10:21:03 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

NICK::NICK(void) : Command(true, false) {
}

void NICK::exec(Message& message, Server* server, Client* client) {
	(void)server;
	if (client->isRegistered() == true) {
		client->sendData(replies::ERR_ALREADYREGISTRED());
		return ;
	}
	std::vector<std::string> params = message.getParams();
	// @todo check if nickname is valid (chars, length)
	if (params[0].empty()) {
		client->sendData(replies::ERR_NONICKNAMEGIVEN());
		return ;
	}
	if (!server->checkNickname(params[0])) {
		client->sendData(replies::ERR_NICKNAMEINUSE(params[0]));
		return ;
	}
    if (!server->checkNicknameValidity(params[0])) {
        client->sendData(replies::ERR_ERRONEUSNICKNAME(params[0]));
        return ;
    }
	if (!client->getNickname().empty()) {
		client->sendData(replies::RPL_NICKCHANGE(client->getNickname(), params[0], client->getUsername()));
	}
	client->setNickname(params[0]);
	this->checkRegistered(client);
}
