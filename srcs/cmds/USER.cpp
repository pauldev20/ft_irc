/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 00:10:41 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/08 18:22:50 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

USER::USER(void) : Command(true, false) {
}

void USER::exec(Message& message, Server* server, Client* client) {
	(void)server;
	if (message.getParams().size() < 4) {
		client->sendData(replies::ERR_NEEDMOREPARAMS(client, "USER"));
		return ;
	}
	if (client->isRegistered() == true) {
		client->sendData(replies::ERR_ALREADYREGISTRED(client));
		return ;
	}
	std::vector<std::string> params = message.getParams();
	client->setUsername(params[0]);
	client->setFullName(params[3]);
	this->checkRegistered(client);
}
