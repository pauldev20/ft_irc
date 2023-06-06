
#include "irc.hpp"
#include "Message.hpp"

#include <iostream>
#include <string>
#include <vector>

void	debug::debugMessage(const Message& message)
{
	std::cout << "prefix: " << message.getPrefix() << std::endl;
	std::cout << "command: " << message.getId() << std::endl;
	std::cout << "params: ";
	for (std::vector<std::string>::const_iterator it = message.getParams().begin(); it != message.getParams().end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}