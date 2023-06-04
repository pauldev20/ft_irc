
#include "irc.hpp"
#include "Command.hpp"

#include <iostream>

typedef void (*cmdFunc)(const Command& command);

static void	cmdKICK(const Command& command)
{
	std::cout << "cmd_id: " << command.getId() << std::endl;
	std::cout << "cmdKICK executed!" << std::endl;
}

static void	cmdINVITE(const Command& command)
{
	std::cout << "cmd_id: " << command.getId() << std::endl;
	std::cout << "cmdINVITE executed!" << std::endl;
}

static void	cmdTOPIC(const Command& command)
{
	std::cout << "cmd_id: " << command.getId() << std::endl;
	std::cout << "cmdTOPIC executed!" << std::endl;
}

static void	cmdMODE(const Command& command)
{
	std::cout << "cmd_id: " << command.getId() << std::endl;
	std::cout << "cmdMODE executed!" << std::endl;
}

static void	cmdPING(const Command& command)
{
	std::cout << "cmd_id: " << command.getId() << std::endl;
	std::cout << "cmdPING executed!" << std::endl;
}

static const cmdFunc exec[] = {
	cmdKICK,
	cmdINVITE,
	cmdTOPIC,
	cmdMODE,
	cmdPING,
};

int	irc::executeCommand(const Command& command)
{
	if (command.getId() < 0 || command.getId() > 4)
		return (ERROR);
	exec[command.getId()](command);
	return (SUCCESS);
}