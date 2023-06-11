/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 07:35:47 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/11 07:35:48 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "Message.hpp"
#include "cmds/Command.hpp"

#include <iostream>

/**
 * This function executes a command from a message object and returns a success status.
 * 
 * @param message A reference to an object of the class Message, which contains information about the
 * message being executed.
 * @param server A pointer to the Server object that the message is being executed on. This object
 * represents the IRC server that the client is connected to.
 * @param client The "client" parameter is a pointer to the client that sent the message.
 * 
 * @return the integer value of the macro "SUCCESS". The value of this macro is not provided in the
 * code snippet, but it is likely defined elsewhere in the codebase.
 */
int	irc::execute_message(Message& message, Server* server, Client* client)
{
	message.getCmd()->execute(message, server, client);

	return (SUCCESS);
}
