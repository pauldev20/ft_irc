
#include "Bot.hpp"
#include <iostream>
#include <cstdlib>

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

	data->server = argv[1];
	// std::string port = argv[2];
	// if (port.find_first_not_of("0123456789+") != std::string::npos()
	// 	return (EXIT_FAILURE);
	// if (.str() != (port.c_str() + (port.find('+') != std::string::npos ? 1 : 0)))
	// 	return (EXIT_FAILURE);
	data->port = atoi(argv[2]);
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