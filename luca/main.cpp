
#include "irc.hpp"
#include "Server.hpp"
#include "Command.hpp"

#include <iostream>

#define PORT 6667

// int main()
// {
// 	Server server;

// 	server.start(PORT);
// 	while (1)
// 		server.acceptClient();
// 	return (0);
// }

int main()
{
	Command command;
	std::string message = ":prefix INVITE param1 param2 :trailing\r\n";

	std::cout << "message: " << message << std::endl;

	int ret = parseMessage(command, message);

	std::cout << "message afterwards: " << message << std::endl;
	debug::debugCommand(command);
	std::cout << "parser ret: " << ret << std::endl;

	std::cout << std::endl;

	ret = executeCommand(command);
	std::cout << "executer ret: " << ret << std::endl;

	return (0);
}

// @note
// parser and executer file names?
// parser and executer classes or member functions of server?
// prefix - do we need it?
// replies?