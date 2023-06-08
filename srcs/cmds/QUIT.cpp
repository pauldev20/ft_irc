/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 01:26:27 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/09 00:46:00 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

QUIT::QUIT(void) : Command(false, false, false) {
}

void QUIT::exec(Message& message, Server* server, Client* client) {
	std::vector<std::string> params = message.getParams();
	std::vector<Channel*> &channels = server->getChannels();
	for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); it++) {
		if ((*it)->isClientInChannel(client)) {
			(*it)->sendMessageToAllExcept(replies::RPL_QUIT(client, params.size() > 0 ? params[0] : "Have fun staying poor!"), client);
			continue ;
		}
	}
	client->sendData(replies::RPL_QUIT(client, params.size() > 0 ? params[0] : "Have fun staying poor!"));
	client->setDisconnected(true);
}
