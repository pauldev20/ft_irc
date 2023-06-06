/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 01:39:14 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/06 01:58:44 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

PRIVMSG::PRIVMSG(void) : Command(false, false) {
}

void PRIVMSG::exec(Message& message, Server* server, Client* client) {
	if (message.getParams().size() < 2) {
		client->addDataToBuffer(replies::ERR_NEEDMOREPARAMS("PRIVMSG"));
		client->sendData();
		return ;
	}
	std::vector<std::string> params = message.getParams();
	Client	*clientTo = server->getClientByNickname(params[0]);
	if (clientTo) {
		clientTo->addDataToBuffer(replies::RPL_PRIVMSG(client->getNickname(), client->getUsername(), clientTo->getNickname(), params[1]));
		clientTo->sendData();
		return;
	}
	Channel	*channelTo = server->getChannelByName(params[0]);
	if (channelTo) {
		if (!channelTo->isClientInChannel(client)) {
			client->addDataToBuffer(replies::ERR_CANNOTSENDTOCHAN(client->getNickname(), channelTo->getName()));
			client->sendData();
			return;
		}
		channelTo->sendMessageToAllExcept(replies::RPL_PRIVMSG(client->getNickname(), client->getUsername(), channelTo->getName(), params[1]), client);
		return;
	}
	client->addDataToBuffer(replies::ERR_NOSUCHNICK(params[0], ""));
	client->sendData();
}