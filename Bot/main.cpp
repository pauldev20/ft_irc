
#include "Bot.hpp"
#include <iostream>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

int	main(int argc, char **argv)
{
	Bot bot;

	if (argc != 5)
	{
		std::cerr << "Usage: " << argv[0]
		<< " <server> <port> <password> <nick>" << std::endl;
		return (EXIT_FAILURE);
	}

	// @todo proper error handling
	std::string server = argv[1];
	int port = std::atoi(argv[2]); // @todo not c++98
	std::string password = argv[3];
	std::string nick = argv[4];

	bot.run(server, port, password, nick);

	return (EXIT_SUCCESS);
}