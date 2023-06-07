/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:08:13 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/07 17:03:20 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

PART::PART(void) : Command(true, true) {
}

void PART::exec(Message& message, Server* server, Client* client) {
	std::vector<std::string> params = message.getParams();
    std::vector<std::string> channel_list = PART::splitString(params[0], ',');
    for (size_t i = 0; i < channel_list.size(); i++) {
        Channel *channel = server->getChannelByName(channel_list[i]);
        if (channel == NULL) {
            client->sendData(replies::ERR_NOSUCHCHANNEL(client->getNickname(), params[0]));
            continue ;
        }
        channel->removeClient(client);
        client->sendData(replies::RPL_PART(client->getNickname(), client->getUsername(), channel->getName(), params[1]));
        if (channel->getClientCount() == 0) {
            server->removeChannel(channel);
        }
    }
}