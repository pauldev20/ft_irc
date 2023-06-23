/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:41:03 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/23 18:46:38 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Command.hpp"
#include "irc.hpp"
#include <string>
#include <sstream>
#include <vector>

/* -------------------------------------------------------------------------- */
/*                                Class Methods                               */
/* -------------------------------------------------------------------------- */

Command::Command(bool needsPass, bool needsRegistration, bool needsParamsCount)
	: checkRegister(needsRegistration), checkPass(needsPass), checkParamsCount(needsParamsCount) {
}

Command::~Command() {
}

/* -------------------------------------------------------------------------- */
/*                               Public Methods                               */
/* -------------------------------------------------------------------------- */

/**
 * The function executes a command based on a message, server, and client,
 * performing various checks before executing.
 *
 * @param message A reference to a Message object, which contains information
 * about the command being executed, including the command name and any parameters.
 * @param server A pointer to the Server object that the command is being executed on.
 * @param client The "client" parameter is a pointer to the client who sent the
 * message that triggered the execution of the command.
 *
 * @return nothing (void). It is using the "return;" statement to exit the
 * function early if certain conditions are met.
 */
void	Command::execute(Message& message, Server* server, Client* client) {
	if (this->checkPass && !client->isAuthenticated()) {
		client->sendData(replies::ERR_PASSWDMISMATCH(client));
		return ;
	}
	if (this->checkRegister && !client->isRegistered()) {
		client->sendData(replies::ERR_NOTREGISTERED(client));
		return ;
	}
	if (this->checkParamsCount && (message.getParams().size() + (message.getTrailing() != "")) < 1) {
		client->sendData(replies::ERR_NEEDMOREPARAMS(client, message.getCmdName()));
		return ;
	}
	this->exec(message, server, client);
}

/**
 * This function splits a string into a vector of substrings
 * based on a specified delimiter.
 * 
 * @param input The input string that needs to be split into tokens.
 * @param delimiter The delimiter is a character that is used to split the input
 * string into smaller substrings. In this function, the delimiter is passed as
 * a parameter and is used to split the input string into smaller substrings.
 * 
 * @return The function `splitString` returns a vector of strings that contains
 * the substrings of the input string that are separated by the specified
 * delimiter character.
 */
std::vector<std::string> Command::splitString(const std::string& input, char delimiter) {
    std::stringstream ss(input);
    std::string item;
    std::vector<std::string> tokens;

    while (std::getline(ss, item, delimiter)) {
        tokens.push_back(item);
    }
    return tokens;
}

/* -------------------------------------------------------------------------- */
/*                               Private Methods                              */
/* -------------------------------------------------------------------------- */

/**
 * The function checks if a client is registered and sends a
 * welcome message if they are.
 *
 * @param client The parameter "client" is a pointer to an
 * object of the class "Client".
 *
 * @return If any of the conditions in the if statement are true, the function
 * will return without doing anything.
 */
void	Command::checkRegistered(Client *client) const {
	if (client->getNickname().empty() || client->getUsername().empty()
		|| client->getFullName().empty() || client->isRegistered())
		return ;
	client->setRegistered(true);
	client->sendData(replies::RPL_WELCOME(client));
}
