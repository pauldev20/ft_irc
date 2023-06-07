/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:08:13 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/07 10:57:40 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

PART::PART(void) : Command(true, true) {
}

void PART::exec(Message& message, Server* server, Client* client) {
	std::vector<std::string> params = message.getParams();
	//@todo this causes segv? error?
	// for (std::vector<std::string>::iterator it = params.begin(); it != params.end(); it++) {
	// 	std::cout << (*it) << std::endl;
	// }
	//@todo implement leaving of multiple! channels
	Channel *channel = server->getChannelByName(params[0]);
	if (channel == NULL) {
		client->sendData(replies::ERR_NOSUCHCHANNEL(client->getNickname(), params[0]));
		return ;
	}
	channel->removeClient(client);
	client->sendData(replies::RPL_PART(client->getNickname(), client->getUsername(), channel->getName(), params[1]));
	if (channel->getClientCount() == 0) {
		server->removeChannel(channel);
	}
}