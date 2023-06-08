/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 01:07:49 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/08 12:25:27 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
#include <sstream>

static int	validPort(std::string port)
{
	int portVal;
	std::ostringstream tmp;
	std::istringstream(port) >> portVal;
	tmp << portVal;
	if (tmp.str() != (port.c_str() + (port.find('+') != std::string::npos ? 1 : 0)))
		return (-1);
	if (port.find_first_not_of("0123456789") != std::string::npos)
		return (-1);
	if (portVal < 1 || portVal > 65535)
		return (-1);
	return (portVal);
}

static bool	validPassword(std::string password)
{
	if (password.length() < 4 || password.length() > 12)
		return (false);
	if (password.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != std::string::npos)
		return (false);
	return (true);
}

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
		int port = validPort(argv[1]);
		if (port < 0) {
			std::cerr << "Invalid port! The port needs to be in the range of 1 - 65535" << std::endl;
			return (1);
		}
		if (!validPassword(argv[2])) {
			std::cerr << "Invalid password! The passowrd needs to be between 4 and 12 characters long and can only consist out of (a-z, A-Z, 0-9)" << std::endl;
			return (1);
		}
		Server server(port, argv[2]);
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
