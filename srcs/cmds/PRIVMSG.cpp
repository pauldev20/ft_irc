/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 01:39:14 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/07 10:08:53 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

PRIVMSG::PRIVMSG(void) : Command(false, false) {
}

void PRIVMSG::exec(Message& message, Server* server, Client* client) {
	if (message.getParams().size() < 2) {
		client->sendData(replies::ERR_NEEDMOREPARAMS("PRIVMSG"));
		return ;
	}
	std::vector<std::string> params = message.getParams();
	Client	*clientTo = server->getClientByNickname(params[0]);
	if (clientTo) {
		clientTo->sendData(replies::RPL_PRIVMSG(client->getNickname(), client->getUsername(), clientTo->getNickname(), params[1]));
		return;
	}
	Channel	*channelTo = server->getChannelByName(params[0]);
	if (channelTo) {
		if (!channelTo->isClientInChannel(client)) {
			client->sendData(replies::ERR_CANNOTSENDTOCHAN(client->getNickname(), channelTo->getName()));
			return;
		}
		channelTo->sendMessageToAllExcept(replies::RPL_PRIVMSG(client->getNickname(), client->getUsername(), channelTo->getName(), params[1]), client);
		return;
	}
	client->sendData(replies::ERR_NOSUCHNICK(params[0], ""));
}