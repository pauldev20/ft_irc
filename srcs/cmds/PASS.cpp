/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:42:44 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/06 15:49:09 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

PASS::PASS(void) : Command(false, false) {
}

void PASS::exec(Message& message, Server* server, Client* client) {
	if (client->isRegistered() == true) {
		client->addDataToBuffer(replies::ERR_ALREADYREGISTRED());
		client->sendData();
		return ;
	}
    if (message.getParams()[0].empty()) {
        client->addDataToBuffer(replies::ERR_NEEDMOREPARAMS("PASS"));
        client->sendData();
        return ;
    }
	if (message.getParams()[0] == server->getPassword())
		client->setAuthenticated(true);
	else {
		client->addDataToBuffer(replies::ERR_PASSWDMISMATCH());
		client->sendData();
	}
}
