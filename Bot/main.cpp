
#include "Bot.hpp"
#include <iostream>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

typedef struct s_data
{
	std::string	server;
	int			port;
	std::string	password;
	std::string	nick;
}	t_data;

int	parse(s_data *data, int argc, char **argv)
{
	if (argc != 5)
	{
		std::cerr << "Usage: " << argv[0]
		<< " <server> <port> <password> <nick>" << std::endl;
		return (EXIT_FAILURE);
	}

	// @todo proper error handling
	data->server = argv[1];
	data->port = std::atoi(argv[2]); // @todo not c++98
	data->password = argv[3];
	data->nick = argv[4];
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	Bot 	bot;
	s_data	data;

	if (parse(&data, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	bot.run(data.server, data.port, data.password, data.nick);

	return (EXIT_SUCCESS);
}