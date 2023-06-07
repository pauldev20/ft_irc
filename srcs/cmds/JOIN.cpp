/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:11:40 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/07 11:30:17 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"
#include "Channel.hpp"

#include <string>
#include <sstream>
#include <vector>

JOIN::JOIN(void) : Command(true, true) {
}

void JOIN::exec(Message& message, Server* server, Client* client) {
	//@todo add check for valid channel name (# and &)?
    std::vector<std::string> channel_list = JOIN::splitString(message.getParams()[0], ',');
    for (size_t i = 0; i < channel_list.size(); i++) {
        Channel *channel = server->getChannelByName(channel_list[i]);
        if (channel == NULL) {
            channel = new Channel(client, channel_list[i]);
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
        client->sendData(replies::RPL_JOIN(client->getNickname(), client->getUsername(), server->getChannelByName(channel_list[i])->getName()));
    }
	//@todo should there be a join message for the others??
	//@todo 353 & 366 replies!
}
