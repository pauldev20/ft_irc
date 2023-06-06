/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CAP.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 20:11:01 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/06 15:49:37 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

CAP::CAP(void) : Command(false, false) {
}

void CAP::exec(Message& message, Server* server, Client* client) {
	(void)server;
	std::vector<std::string> params = message.getParams();
	if (params[0] == "LS") {
		client->addDataToBuffer(replies::RPL_CAP());
		client->sendData();
	}
}
