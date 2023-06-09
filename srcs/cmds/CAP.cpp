/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CAP.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 20:11:01 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/09 22:50:44 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

CAP::CAP(void) : Command(false, false) {
}

/**
 * The function checks if the first parameter of a message is "LS" and sends a reply to the client if
 * it is.
 * 
 * @param message A reference to a Message object, which likely contains information about a client's
 * message to the server.
 * @param server A pointer to the Server object that received the message.
 * @param client The "client" parameter is a pointer to the client who sent the CAP command.
 */
void CAP::exec(Message& message, Server* server, Client* client) {
	(void)server;
	std::vector<std::string> params = message.getParams();
	if (params[0] == "LS") {
		client->sendData(replies::RPL_CAP());
	}
}
