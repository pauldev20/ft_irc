/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 01:39:14 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/23 18:57:41 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

PRIVMSG::PRIVMSG(void) : Command() {
}

/**
 * This function sends a message to one or multiple clients
 * or channels on a server.
 * 
 * @param message A reference to a Message object, which contains
 * information about the incoming message.
 * @param server A pointer to the Server object that the PRIVMSG
 * command is being executed on.
 * @param client A pointer to the client who sent the PRIVMSG command.
 * 
 * @return The function does not return anything, it uses the "return;"
 * statement to exit the function early in case of an error.
 */
void PRIVMSG::exec(Message& message, Server* server, Client* client) {
	std::vector<std::string> params = message.getParams();
	if (params.size() < 1 || message.getTrailing().empty()) {
		client->sendData(replies::ERR_NEEDMOREPARAMS(client, "PRIVMSG"));
		return ;
	}
	std::vector<std::string> target_list = this->splitString(params[0], ',');
	for (size_t i = 0; i < target_list.size(); i++) {
		Client *clientTo = server->getClientByNickname(target_list[i]);
		if (clientTo) {
            if (!clientTo->isRegistered()) {
                client->sendData(replies::ERR_NOSUCHNICK(client, target_list[i]));
                continue ;
            }
			clientTo->sendData(replies::RPL_PRIVMSG(client, clientTo->getNickname(), message.getTrailing()));
			continue ;
		}
		Channel	*channelTo = server->getChannelByName(target_list[i]);
		if (channelTo) {
			if (!channelTo->isClientInChannel(client)) {
				client->sendData(replies::ERR_CANNOTSENDTOCHAN(client, channelTo->getName()));
				continue ;
			}
			channelTo->sendMessageToAllExcept(replies::RPL_PRIVMSG(client, channelTo->getName(), message.getTrailing()), client);
			continue ;
		}
		client->sendData(replies::ERR_NOSUCHNICK(client, target_list[i]));
	}
}
