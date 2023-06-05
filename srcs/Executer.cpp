
#include "irc.hpp"
#include "Command.hpp"

#include <iostream>

typedef void (*cmdFunc)(const Command& command, const Server* server, const Client* client);

static void	cmdKICK(const Command& command, const Server* server, const Client* client)
{
	std::cout << "cmd_id: " << command.getId() << std::endl;
	std::cout << "cmdKICK executed!" << std::endl;
	(void)server;
	(void)client;
}

static void	cmdINVITE(const Command& command, const Server* server, const Client* client)
{
	std::cout << "cmd_id: " << command.getId() << std::endl;
	std::cout << "cmdINVITE executed!" << std::endl;
	(void)server;
	(void)client;
}

static void	cmdTOPIC(const Command& command, const Server* server, const Client* client)
{
	std::cout << "cmd_id: " << command.getId() << std::endl;
	std::cout << "cmdTOPIC executed!" << std::endl;
	(void)server;
	(void)client;
}

static void	cmdMODE(const Command& command, const Server* server, const Client* client)
{
	std::cout << "cmd_id: " << command.getId() << std::endl;
	std::cout << "cmdMODE executed!" << std::endl;
	(void)server;
	(void)client;
}

static void	cmdPING(const Command& command, const Server* server, const Client* client)
{
	std::cout << "cmd_id: " << command.getId() << std::endl;
	std::cout << "cmdPING executed!" << std::endl;
	(void)server;
	(void)client;
}

static const cmdFunc exec[] = {
	cmdKICK,
	cmdINVITE,
	cmdTOPIC,
	cmdMODE,
	cmdPING,
};

int	irc::executeCommand(const Command& command, const Server* server, const Client* client)
{
	if (command.getId() < 0 || command.getId() > 4)
		return (ERROR);
	exec[command.getId()](command, server, client);
	return (SUCCESS);
}
