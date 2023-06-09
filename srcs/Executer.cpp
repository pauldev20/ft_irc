
#include "irc.hpp"
#include "Message.hpp"
#include "cmds/Command.hpp"

#include <iostream>

int	irc::execute_message(Message& message, Server* server, Client* client)
{
	message.getCmd()->execute(message, server, client);

	return (SUCCESS);
}
