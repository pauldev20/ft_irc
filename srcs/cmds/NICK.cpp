/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 23:17:01 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/07 17:07:56 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

static bool    checkNicknameValidity(std::string const &nickname) {
    if (nickname.empty())
        return (false);
    if (nickname.length() > 16)
        return (false);
    for (size_t i = 0; i < nickname.length(); i++) {
        if (i == 0 && (!isalpha(nickname[i]) && nickname[i] != '_' && nickname[i] != '-'))
            return (false);
        if (!std::isalnum(nickname[i]) && nickname[i] != '_' && nickname[i] != '-')
            return (false);
    }
    return (true);
}

NICK::NICK(void) : Command(true, false) {
}

void NICK::exec(Message& message, Server* server, Client* client) {
	(void)server;
	if (client->isRegistered() == true) {
		client->sendData(replies::ERR_ALREADYREGISTRED());
		return ;
	}
	std::vector<std::string> params = message.getParams();
	if (params[0].empty()) {
		client->sendData(replies::ERR_NONICKNAMEGIVEN());
		return ;
	}
    if (!checkNicknameValidity(params[0])) {
        client->sendData(replies::ERR_ERRONEUSNICKNAME(params[0]));
        return ;
    }
	if (!server->checkNickname(params[0])) {
		client->sendData(replies::ERR_NICKNAMEINUSE(params[0]));
		return ;
	}
	if (!client->getNickname().empty()) {
		client->sendData(replies::RPL_NICKCHANGE(client->getNickname(), params[0], client->getUsername()));
	}
	client->setNickname(params[0]);
	this->checkRegistered(client);
}
