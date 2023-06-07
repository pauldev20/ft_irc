/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:11:40 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/07 17:05:44 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"
#include "Channel.hpp"
#include <sstream>	// std::stringstream
#include <vector>	// std::vector

static bool	checkChannelNameValidity(std::string const &name) {
	if (name.size() > 0 && name[0] != '#') {
		return false;
	}
	return true;
}

JOIN::JOIN(void) : Command(true, true) {
}

void JOIN::exec(Message& message, Server* server, Client* client) {
    std::vector<std::string> channel_list = JOIN::splitString(message.getParams()[0], ',');
    for (size_t i = 0; i < channel_list.size(); i++) {
		if (checkChannelNameValidity(channel_list[i]) == false) {
			client->sendData(replies::ERR_NOSUCHCHANNEL(client->getNickname(), message.getParams()[0]));
			continue ;
		}
        Channel *channel = server->getChannelByName(channel_list[i]);
        if (channel == NULL) {
            channel = new Channel(client, channel_list[i]);
            server->addChannel(channel);
        } else {
            try {
                channel->addClient(client);
            } catch (const Channel::ChannelFullExcpetion &e) {
                client->sendData(replies::ERR_CHANNELISFULL(client->getNickname(), channel->getName()));
                continue ;
            } catch (const Channel::InviteOnlyExcpetion &e) {
                client->sendData(replies::ERR_INVITEONLYCHAN(client->getNickname(), channel->getName()));
                continue ;
            } catch (const Channel::AllreadyInChannelExcpetion &e) {
                client->sendData(replies::ERR_CHANNELISFULL(client->getNickname(), channel->getName()));
                continue ;
            }
        }
		channel->sendMessageToAll(replies::RPL_JOIN(client->getNickname(), client->getUsername(), channel->getName()));
		client->sendData(replies::RPL_NAMREPLY(client->getNickname(), channel->getName(), channel->getClientList()));
		client->sendData(replies::RPL_ENDOFNAMES(client->getNickname(), channel->getName()));
    }
}
