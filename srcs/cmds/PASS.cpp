/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:42:44 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/08 18:22:29 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

PASS::PASS(void) : Command(false, false) {
}

void PASS::exec(Message& message, Server* server, Client* client) {
	if (client->isRegistered() == true) {
		client->sendData(replies::ERR_ALREADYREGISTRED(client));
		return ;
	}
    if (message.getParams()[0].empty()) {
        client->sendData(replies::ERR_NEEDMOREPARAMS(client, "PASS"));
        return ;
    }
	if (message.getParams()[0] == server->getPassword())
		client->setAuthenticated(true);
	else {
		client->sendData(replies::ERR_PASSWDMISMATCH(client));
	}
}
