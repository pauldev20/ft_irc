/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 01:05:02 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/23 18:56:13 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

PING::PING(void) : Command(false, false) {
}

/**
 * The PING::exec function sends a reply message to a client
 * with the specified parameter.
 * 
 * @param message The `Message` object contains information about the
 * incoming message, such as the command and parameters.
 * @param server The "server" parameter is not used in this function
 * and is therefore not relevant.
 * @param client The "client" parameter is a pointer to the
 * client who sent the PING message.
 */
void PING::exec(Message& message, Server* server, Client* client) {
	(void)server;
	std::vector<std::string> params = message.getParams();
	if (params.size() == 1) {
		client->sendData(replies::RPL_PING(params[0]));
	} else {
		std::string pings = "";
		for (size_t i = 1; i < params.size(); i++)
			pings += params[i] + " ";
		client->sendData(replies::RPL_PING(pings));
	}
}
