/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:42:44 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/09 22:53:53 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

PASS::PASS(void) : Command(false, false) {
}

/**
 * This function checks if a client's password matches the server's password and sets the client as
 * authenticated if it does.
 * 
 * @param message The message received from the client, which includes the PASS command and its
 * parameters.
 * @param server A pointer to the Server object that the client is connected to.
 * @param client The "client" parameter is a pointer to the client who sent the PASS command.
 * 
 * @return nothing (void). It uses the "return;" statement to exit the function early in case of
 * certain conditions being met.
 */
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
