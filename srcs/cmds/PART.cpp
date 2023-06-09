/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:08:13 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/09 00:46:15 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

PART::PART(void) : Command() {
}

void PART::exec(Message& message, Server* server, Client* client) {
	std::vector<std::string> params = message.getParams();
    std::vector<std::string> channel_list = this->splitString(params[0], ',');
    for (size_t i = 0; i < channel_list.size(); i++) {
        Channel *channel = server->getChannelByName(channel_list[i]);
        if (channel == NULL) {
            client->sendData(replies::ERR_NOSUCHCHANNEL(client, params[0]));
            continue ;
        }
        channel->sendMessageToAll(replies::RPL_PART(client, channel->getName(), message.getTrailing()));
        channel->removeClient(client);
        if (channel->getClientCount() == 0) {
            server->removeChannel(channel);
        }
    }
}
