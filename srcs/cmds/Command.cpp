/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:41:03 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/06 00:46:20 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Command.hpp"
#include "irc.hpp"

Command::Command(bool needsPass, bool needsRegistration) : checkRegister(needsRegistration), checkPass(needsPass) {
	// this->checkRegister;
	// this->checkPass;
}

Command::~Command() {
}

void Command::execute(Message& message, Server* server, Client* client) {
	if (this->checkPass && !client->isAuthenticated()) {
		client->addDataToBuffer(replies::ERR_PASSWDMISMATCH());
		client->sendData();
		return ;
	}
	if (this->checkRegister && !client->isRegistered()) {
		client->addDataToBuffer(replies::ERR_NOTREGISTERED());
		client->sendData();
		return ;
	}
	if (message.getParams().size() < 1) {
		client->addDataToBuffer(replies::ERR_NEEDMOREPARAMS("")); // @todo need command name from message class!!
		client->sendData();
		return ;
	}
	this->exec(message, server, client);
}
