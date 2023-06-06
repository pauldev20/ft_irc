/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:11:40 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/06 14:07:48 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"
#include "Channel.hpp"

JOIN::JOIN(void) : Command(true, true) {
}

void JOIN::exec(Message& message, Server* server, Client* client) {
	//@todo add check for valid channel name (# and &)?
	std::cout << "JOIN" << std::endl;
	Channel *channel = server->getChannelByName(message.getParams()[0]);
	if (channel == NULL) {
		channel = new Channel(client, message.getParams()[0]);
		server->addChannel(channel);
	} else {
		try {
			channel->addClient(client);
		} catch (const Channel::ChannelFullExcpetion &e) {
			client->addDataToBuffer(replies::ERR_CHANNELISFULL(client->getNickname(), channel->getName()));
			client->sendData();
			return ;
		} catch (const Channel::InviteOnlyExcpetion &e) {
			client->addDataToBuffer(replies::ERR_INVITEONLYCHAN(client->getNickname(), channel->getName()));
			client->sendData();
			return ;
		} catch (const Channel::KickedClientExcpetion &e) {
			client->addDataToBuffer(replies::ERR_BANNEDFROMCHAN(client->getNickname(), channel->getName()));
			client->sendData();
			return ;
		} catch (const Channel::AllreadyInChannelExcpetion &e) {
			client->addDataToBuffer(replies::ERR_CHANNELISFULL(client->getNickname(), channel->getName()));
			client->sendData();
			return ;
		}
	}
	client->addDataToBuffer(replies::RPL_JOIN(client->getNickname(), client->getUsername(), channel->getName()));
	client->sendData();
}
