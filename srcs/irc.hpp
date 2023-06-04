
#ifndef IRC_HPP
#define IRC_HPP

#include "Command.hpp"
#include "Server.hpp"

namespace debug
{
	void	debugCommand(const Command& command);
}

namespace irc
{
	int		parseMessage(Command& command, std::string& message);
	int		executeCommand(const Command& command, const Server* server, const Client* client);
}

#endif