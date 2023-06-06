/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:08:13 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/06 11:25:37 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

PART::PART(void) : Command(true, true) {
}

void PART::exec(Message& message, Server* server, Client* client) {
	std::vector<std::string> params = message.getParams();
	//@todo implement leaving of multiple! channels
	Channel *channel = server->getChannelByName(params[0]);
	// if (channel == NULL) {
	// 	client->addDataToBuffer(replies::ERR_NOSUCHCHANNEL(client->getNickname(), params[0]));
	// 	client->sendData();
	// 	return ;
	// }
	channel->removeClient(client);
	client->addDataToBuffer(replies::RPL_PART(client->getNickname(), client->getUsername(), channel->getName(), params[1]));
	client->sendData();
	if (channel->getClientCount() == 0) {
		server->removeChannel(channel);
	}
}