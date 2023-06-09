/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 01:39:14 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/09 00:38:19 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

PRIVMSG::PRIVMSG(void) : Command() {
}

void PRIVMSG::exec(Message& message, Server* server, Client* client) {
	if (message.getParams().size() < 2) {
		client->sendData(replies::ERR_NEEDMOREPARAMS(client, "PRIVMSG"));
		return ;
	}
	std::vector<std::string> params = message.getParams();
	std::vector<std::string> target_list = this->splitString(params[0], ',');
	for (size_t i = 0; i < target_list.size(); i++) {
		Client	*clientTo = server->getClientByNickname(target_list[i]);
		if (clientTo) {
            if (!clientTo->isRegistered()) {
                client->sendData(replies::ERR_NOSUCHNICK(client, target_list[i]));
                continue ;
            }
			clientTo->sendData(replies::RPL_PRIVMSG(client, clientTo->getNickname(), params[1]));
			continue ;
		}
		Channel	*channelTo = server->getChannelByName(target_list[i]);
		if (channelTo) {
			if (!channelTo->isClientInChannel(client)) {
				client->sendData(replies::ERR_CANNOTSENDTOCHAN(client, channelTo->getName()));
				continue ;
			}
			channelTo->sendMessageToAllExcept(replies::RPL_PRIVMSG(client, channelTo->getName(), params[1]), client);
			continue ;
		}
		client->sendData(replies::ERR_NOSUCHNICK(client, target_list[i]));
	}
}
