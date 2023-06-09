/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 23:17:01 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/09 22:53:17 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

/**
 * The function checks if a given nickname is valid based on certain criteria.
 * 
 * @param nickname The parameter "nickname" is a constant reference to a string, which is the nickname
 * that needs to be checked for validity.
 * 
 * @return a boolean value, either true or false.
 */
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

/**
 * This function checks if a client's chosen nickname is valid and available, and sets it if so.
 * 
 * @param message A reference to a Message object, which contains information about the client's
 * message.
 * @param server A pointer to the Server object that the client is connected to.
 * @param client The "client" parameter is a pointer to the client who sent the NICK command.
 * 
 * @return nothing (void). It sends a reply message to the client if certain conditions are met, but it
 * does not return any value.
 */
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
