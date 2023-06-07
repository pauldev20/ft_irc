/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:08:14 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/07 17:08:49 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

KICK::KICK(void) : Command() {
}

void KICK::exec(Message& message, Server* server, Client* client) {
    std::vector<std::string> params = message.getParams();
    if (params.size() < 2) {
        client->sendData(replies::ERR_NEEDMOREPARAMS("KICK"));
        return ;
    }
    std::vector<std::string> channel_list = KICK::splitString(params[0], ',');
    for (size_t i = 0; i < channel_list.size(); i++) {
        Channel *channel = server->getChannelByName(channel_list[i]);
        if (channel->checkChannelNameValidity(params[0]) == false) {
            client->sendData(replies::ERR_NOSUCHCHANNEL(client->getNickname(), channel_list[i]));
            continue ;
        }
        if (channel == NULL) {
            client->sendData(replies::ERR_NOSUCHCHANNEL(client->getNickname(), channel_list[i]));
            continue ;
        }
        if (!channel->isClientInChannel(client)) {
            client->sendData(replies::ERR_NOTONCHANNEL(client->getNickname(), channel_list[i]));
            continue ;
        }
        Client *target = server->getClientByNickname(params[1]);
        if (target == NULL) {
            client->sendData(replies::ERR_NOSUCHNICK(client->getNickname(), channel_list[i]));
            continue ;
        }
        if (!channel->isClientInChannel(target)) {
            client->sendData(replies::ERR_USERNOTINCHANNEL(params[1], channel_list[i]));
            continue ;
        }
        channel->removeClient(target);
        channel->sendMessageToAll(replies::RPL_KICK(client->getNickname(), client->getUsername(), channel_list[i], params[1], params.size() > 2 ? params[2] : ""));
    }
}
