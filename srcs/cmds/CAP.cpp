/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CAP.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 20:11:01 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/07 09:57:29 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

CAP::CAP(void) : Command(false, false) {
}

void CAP::exec(Message& message, Server* server, Client* client) {
	(void)server;
	std::vector<std::string> params = message.getParams();
	if (params[0] == "LS") {
		client->sendData(replies::RPL_CAP());
	}
}
