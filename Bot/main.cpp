
#include "Bot.hpp"
#include <iostream>
#include <cstdlib>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

typedef struct s_data
{
	int			port;
	std::string	password;
	std::string	nick;
}	t_data;

int	parse(s_data *data, int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0]
		<< " <port> <password> <nick>" << std::endl;
		return (EXIT_FAILURE);
	}
	data->port = atoi(argv[1]);
	data->password = argv[2];
	data->nick = argv[3];
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	Bot 	bot;
	s_data	data;

	if (parse(&data, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	bot.run(data.port, data.password, data.nick);
	return (EXIT_SUCCESS);
}