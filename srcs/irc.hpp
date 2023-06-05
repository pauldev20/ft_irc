
#ifndef IRC_HPP
#define IRC_HPP

#include "Command.hpp"
#include "Server.hpp"

#define ERROR -1
#define SUCCESS 0
#define PARAM_MAX 15

namespace debug
{
	void	printCommand(const Command& command);
}

namespace irc
{
	int		parseMessage(Command& command, std::string& message);
	int		executeCommand(const Command& command, const Server* server, const Client* client);
}

#endif