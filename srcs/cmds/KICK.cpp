/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:08:14 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/07 17:19:03 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

KICK::KICK(void) : Command() {
}

//@todo kick multiple users
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
        std::vector<std::string> target_list = KICK::splitString(params[1], ',');
        for (size_t j = 0; j < target_list.size(); j++) {
            Client* target = server->getClientByNickname(target_list[j]);
            if (target == NULL) {
                client->sendData(replies::ERR_NOSUCHNICK(client->getNickname(), channel_list[i]));
                continue ;
            }
            if (!channel->isClientInChannel(target)) {
                client->sendData(replies::ERR_USERNOTINCHANNEL(target_list[j], channel_list[i]));
                continue ;
            }
            channel->sendMessageToAll(replies::RPL_KICK(client->getNickname(), client->getUsername(), channel_list[i], target_list[j], params.size() > 2 ? params[2] : ""));
            channel->removeClient(target);
        }
    }
}
