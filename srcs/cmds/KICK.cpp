/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:08:14 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/09 18:40:18 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

KICK::KICK(void) : Command() {
}

void KICK::exec(Message& message, Server* server, Client* client) {
    std::vector<std::string> params = message.getParams();
    if (params.size() < 1 || message.getTrailing().empty()) {
        client->sendData(replies::ERR_NEEDMOREPARAMS(client, "KICK"));
        return ;
    }
    std::vector<std::string> channel_list = this->splitString(params[0], ',');
    for (size_t i = 0; i < channel_list.size(); i++) {
        Channel *channel = server->getChannelByName(channel_list[i]);
        if (channel->checkChannelNameValidity(params[0]) == false) {
            client->sendData(replies::ERR_NOSUCHCHANNEL(client, channel_list[i]));
            continue ;
        }
        if (channel == NULL) {
            client->sendData(replies::ERR_NOSUCHCHANNEL(client, channel_list[i]));
            continue ;
        }
        if (!channel->isClientInChannel(client)) {
            client->sendData(replies::ERR_NOTONCHANNEL(client, channel_list[i]));
            continue ;
        }
        std::vector<std::string> target_list = this->splitString(params[1], ',');
        for (size_t j = 0; j < target_list.size(); j++) {
            Client* target = server->getClientByNickname(target_list[j]);
            if (target == NULL) {
                client->sendData(replies::ERR_NOSUCHNICK(client, channel_list[i]));
                continue ;
            }
            if (!channel->isClientInChannel(target)) {
                client->sendData(replies::ERR_USERNOTINCHANNEL(target, channel_list[i]));
                continue ;
            }
            channel->sendMessageToAll(replies::RPL_KICK(client, channel_list[i], target_list[j], message.getTrailing()));
            channel->removeClient(target);
        }
    }
}
