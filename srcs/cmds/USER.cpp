/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 00:10:41 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/07 10:22:46 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

USER::USER(void) : Command(true, false) {
}

void USER::exec(Message& message, Server* server, Client* client) {
	(void)server;
	if (message.getParams().size() < 4) {
		client->sendData(replies::ERR_NEEDMOREPARAMS("USER"));
		return ;
	}
	if (client->isRegistered() == true) {
		client->sendData(replies::ERR_ALREADYREGISTRED());
		return ;
	}
	std::vector<std::string> params = message.getParams();
	client->setUsername(params[0]);
	client->setFullName(params[3]);
	this->checkRegistered(client);
}
