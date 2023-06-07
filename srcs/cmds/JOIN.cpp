/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:11:40 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/07 15:05:18 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"
#include "Channel.hpp"

static bool	checkChannelNameValidity(std::string const &name) {
	if (name.size() > 0 && name[0] != '#') {
		return false;
	}
	return true;
}

JOIN::JOIN(void) : Command() {
}

void JOIN::exec(Message& message, Server* server, Client* client) {
	if (checkChannelNameValidity(message.getParams()[0]) == false) {
		client->sendData(replies::ERR_NOSUCHCHANNEL(client->getNickname(), message.getParams()[0]));
		return ;
	}
	Channel *channel = server->getChannelByName(message.getParams()[0]);
	if (channel == NULL) {
		channel = new Channel(client, message.getParams()[0]);
		server->addChannel(channel);
	} else {
		try {
			channel->addClient(client);
		} catch (const Channel::ChannelFullExcpetion &e) {
			client->sendData(replies::ERR_CHANNELISFULL(client->getNickname(), channel->getName()));
			return ;
		} catch (const Channel::InviteOnlyExcpetion &e) {
			client->sendData(replies::ERR_INVITEONLYCHAN(client->getNickname(), channel->getName()));
			return ;
		} catch (const Channel::AllreadyInChannelExcpetion &e) {
			client->sendData(replies::ERR_CHANNELISFULL(client->getNickname(), channel->getName()));
			return ;
		}
	}
	channel->sendMessageToAll(replies::RPL_JOIN(client->getNickname(), client->getUsername(), channel->getName()));
	client->sendData(replies::RPL_NAMREPLY(client->getNickname(), channel->getName(), channel->getClientList()));
	client->sendData(replies::RPL_ENDOFNAMES(client->getNickname(), channel->getName()));
}
