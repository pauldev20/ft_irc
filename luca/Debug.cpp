
#include "irc.hpp"
#include "Command.hpp"

#include <iostream>
#include <string>
#include <vector>

void	debug::debugCommand(const Command& command)
{
	std::cout << "prefix: " << command.getPrefix() << std::endl;
	std::cout << "command: " << command.getId() << std::endl;
	std::cout << "params: ";
	for (std::vector<std::string>::const_iterator it = command.getParams().begin(); it != command.getParams().end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}