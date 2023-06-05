/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 01:07:49 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/05 15:56:45 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "./ircserv <port> <password>" << std::endl;
		return (1);
	}

	std::cout << std::endl;
	std::cout << "\033[34m███████ ████████         ██ ██████   ██████\033[0m" << std::endl;
	std::cout << "\033[34m██         ██            ██ ██   ██ ██     \033[0m" << std::endl;
	std::cout << "\033[34m█████      ██            ██ ██████  ██     \033[0m" << std::endl;
	std::cout << "\033[34m██         ██            ██ ██   ██ ██     \033[0m" << std::endl;
	std::cout << "\033[34m██         ██    ███████ ██ ██   ██  ██████\033[0m" << std::endl;
	std::cout << std::endl;

	try {
		Server server(atoi(argv[1]), argv[2]);
		std::cout << "\033[33mServer starting...\033[0m" << std::endl;
		server.start();
		std::cout << "\033[0;97mServer listening on port: \033[32m" << server.getPort() << "\033[0m" << std::endl;
		while (1)
			server.run();
	} catch (int errcode) {
		return (errcode);
	}

	return (0);
}
