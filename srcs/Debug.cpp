
#include "irc.hpp"
#include "Message.hpp"

#include <iostream>
#include <string>
#include <vector>

void	debug::printMessage(const Message& command)
{
	std::cout << "prefix: " << command.getPrefix() << std::endl;
	std::cout << "params:" << std::endl;
	for (std::vector<std::string>::const_iterator it = command.getParams().begin(); it != command.getParams().end(); it++)
		std::cout << "	[" << *it << "]" << std::endl;
	std::cout << "trailing: " << command.getTrailing() << std::endl;
	std::cout << "is trailing empty: " << command.isTrailingEmpty() << std::endl;
	std::cout << std::endl;
}