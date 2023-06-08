/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 23:17:01 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/08 19:33:47 by pgeeser          ###   ########.fr       */
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
		client->sendData(replies::ERR_ALREADYREGISTRED(client));
		return ;
	}
	std::vector<std::string> params = message.getParams();
	if (params[0].empty()) {
		client->sendData(replies::ERR_NONICKNAMEGIVEN(client));
		return ;
	}
    if (!checkNicknameValidity(params[0])) {
        client->sendData(replies::ERR_ERRONEUSNICKNAME(client, params[0]));
        return ;
    }
	if (!server->checkNickname(params[0])) {
		client->sendData(replies::ERR_NICKNAMEINUSE(client, params[0]));
		return ;
	}
	client->setNickname(params[0]);
	this->checkRegistered(client);
}
