
#include "irc.hpp"
#include "Message.hpp"
#include "cmds/Commands.hpp"

#include <iostream>

typedef void (*cmdFunc)(Message& message, Server* server, Client* client);

static void	cmdCAP(Message& message, Server* server, Client* client)
{
	CAP().execute(message, server, client);
}

static void	cmdPING(Message& message, Server* server, Client* client)
{
	PING().execute(message, server, client);
}

static void	cmdPASS(Message& message, Server* server, Client* client)
{
	PASS().execute(message, server, client);
}

static void	cmdNICK(Message& message, Server* server, Client* client)
{
	NICK().execute(message, server, client);
}

static void	cmdUSER(Message& message, Server* server, Client* client)
{
	USER().execute(message, server, client);
}

static void	cmdQUIT(Message& message, Server* server, Client* client)
{
	QUIT().execute(message, server, client);
}

static void	cmdPRIVMSG(Message& message, Server* server, Client* client)
{
	PRIVMSG().execute(message, server, client);
}

static void	cmdJOIN(Message& message, Server* server, Client* client)
{
	JOIN().execute(message, server, client);
}

static void	cmdPART(Message& message, Server* server, Client* client)
{
	PART().execute(message, server, client);
}

static const cmdFunc exec[] = {
	cmdCAP,
	cmdPING,
	cmdPASS,
	cmdNICK,
	cmdUSER,
	cmdQUIT,
	cmdPRIVMSG,
	cmdJOIN,
	cmdPART
};

int	irc::executeMessage(Message& message, Server* server, Client* client)
{
	if (message.getId() < 0 || message.getId() > 7)
		return (ERROR);
	exec[message.getId()](message, server, client);
	return (SUCCESS);
}
