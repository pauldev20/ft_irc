
#include "Bot.hpp"
#include <iostream>
#include <string>
#include <cstring> // for std::strlen
#include <cstdlib> // for std::exit
#include <sys/socket.h> // for socket
#include <arpa/inet.h> // for inet_addr
#include <unistd.h> // for close

#define ERROR -1
#define SUCCESS 0

Bot::Bot() : _fd(0)
{
}

Bot::~Bot()
{
}

static int	connect_to_server(std::string server, int port)
{
	int					fd;
	struct sockaddr_in	serv_addr;
	
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
	{
		std::cerr << "\nSocket creation error \n";
		return (ERROR);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if (connect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cerr << "\nConnection Failed \n";
		return (ERROR);
	}
	return (fd);
}

static void	send_auth(int fd, std::string pass, std::string nick)
{
	std::string	command;

	command = "PASS " + pass + "\r\n";
	send(fd, command.c_str(), command.length(), 0);
	command = "NICK " + nick + "\r\n";
	send(fd, command.c_str(), command.length(), 0);
}

static bool	got_contacted(int fd)
{
	char		buffer[2048];
	std::string	message;
	std::string	command;

	std::memset(buffer, 0, sizeof(buffer));
	if (recv(fd, buffer, sizeof(buffer), 0) > 0)
	{
		message = buffer;
		std::size_t pos = message.find("PRIVMSG");
		if(pos != std::string::npos)
			return (true);
	}
	// @todo exception when recv returns -1
	return (false);
}

// @todo add error handling
static int	send_message(int fd, std::string message)
{
	std::string	command;

	command = "PRIVMSG lorbke :" + message + "\r\n";
	send(fd, command.c_str(), command.length(), 0);
	return (SUCCESS);
}

static const std::string answer[8] =
{
	"I just wanna tell you how I'm feeling\n",
	"Gotta make you understand\n",
	"Never gonna give you up\n",
	"Never gonna let you down\n",
	"Never gonna run around and desert you\n",
	"Never gonna make you cry\n",
	"Never gonna say goodbye\n",
	"Never gonna tell a lie and hurt you\n",
};

void	Bot::run(std::string server, int port, std::string pass, std::string nick)
{
	this->_fd = connect_to_server(server, port);
	if (this->_fd == ERROR)
		std::exit(EXIT_FAILURE);
	send_auth(this->_fd, pass, nick);
	while (true)
	{
		char		buffer[2048];
		std::string	message;
		std::string	command;

		std::memset(buffer, 0, sizeof(buffer));
		if (recv(this->_fd, buffer, sizeof(buffer), 0) > 0)
		{
			message = buffer;
			std::size_t pos = message.find("PRIVMSG");
			if(pos != std::string::npos)
			{
				for (int i = 0; i < 8; i++)
				{
					sleep(2);
					send_message(this->_fd, answer[i]);
				}
			}
		}
		// @todo exception when recv returns -1
	}
}

// "We're no strangers to love\nYou know the rules and so do I (do I)\nA full commitment's what I'm thinking of\nYou wouldn't get this from any other guy\nI just wanna tell you how I'm feeling\nGotta make you understand\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\nWe've known each other for so long\nYour heart's been aching, but you're too shy to say it (say it)\nInside, we both know what's been going on (going on)\nWe know the game and we're gonna play it\nAnd if you ask me how I'm feeling\nDon't tell me you're too blind to see\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\nWe've known each other for so long\nYour heart's been aching, but you're too shy to say it (to say it)\nInside, we both know what's been going on (going on)\nWe know the game and we're gonna play it\nI just wanna tell you how I'm feeling\nGotta make you understand\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you