/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 01:26:27 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/07 10:57:07 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

QUIT::QUIT(void) : Command(false, false) {
}

void QUIT::exec(Message& message, Server* server, Client* client) {
	(void)server;
	(void)message;
	// @todo is a quit message possible/needed?
	client->sendData(replies::RPL_QUIT(client->getNickname(), client->getUsername()));	//@todo is this really correct? username?
	client->setDisconnected(true);
}