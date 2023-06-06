
#include "irc.hpp"
#include "Message.hpp"
#include "cmds/Commands.hpp"
#include <vector>

#include <iostream>

std::vector<Command*> exec = {
	&CAP(),
	&PING(),
	&PASS(),
	&NICK(),
	&USER(),
	&QUIT(),
	&PRIVMSG(),
	&JOIN(),
	&PART()
};

int	irc::executeMessage(Message& message, Server* server, Client* client)
{
	if (message.getId() < 0 || message.getId() > 7)
		return (ERROR);
	exec[message.getId()]->execute(message, server, client);
	return (SUCCESS);
}
