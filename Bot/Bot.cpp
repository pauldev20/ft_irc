
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
#define PRIVMSG "PRIVMSG"

#define SYSERR "System error: "
#define ERR_FAILEDSEND "Failed to send message to server"
#define ERR_FAILEDCONNECT "Failed to connect to server"
#define ERR_FAILEDSOCKET "Failed to create socket"
#define ERR_FAILEDRECV "Failed to receive message from server"

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

Bot::Bot() : _fd(0)
{
}

Bot::~Bot()
{
}

static int	connect_to_server(int port)
{
	int					fd;
	struct sockaddr_in	serv_addr;
	
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
		throw std::system_error(errno, std::system_category(), ERR_FAILEDSOCKET);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if (connect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		throw std::system_error(errno, std::system_category(), ERR_FAILEDCONNECT);
	return (fd);
}

static void	send_auth(int fd, std::string pass, std::string nick)
{
	std::string	command;

	command = "PASS " + pass + "\r\n";
	if (send(fd, command.c_str(), command.length(), 0) < 0)
		throw std::system_error(errno, std::system_category(), ERR_FAILEDSEND);
	command = "NICK " + nick + "\r\n";
	if (send(fd, command.c_str(), command.length(), 0) < 0)
		throw std::system_error(errno, std::system_category(), ERR_FAILEDSEND);
	command = "USER " + nick + " 0 * :" + nick + "\r\n";
	if (send(fd, command.c_str(), command.length(), 0) < 0)
		throw std::system_error(errno, std::system_category(), ERR_FAILEDSEND);
}

static int	send_message(int fd, std::string message, std::string nick)
{
	std::string	command;

	command = "PRIVMSG " + nick + " :" + message + "\r\n";
	if (send(fd, command.c_str(), command.length(), 0) < 0)
		throw std::system_error(errno, std::system_category(), ERR_FAILEDSEND);
	return (SUCCESS);
}

static std::string	get_nick_from_privmsg(std::string message)
{
	std::size_t	start = message.find(":") + 1;
	std::size_t	end = message.find("!") - 1;
	std::string	nick = message.substr(start, end);
	return (nick);
}

void	Bot::run(int port, std::string pass, std::string nick)
{
	try
	{
		this->_fd = connect_to_server(port);
		send_auth(this->_fd, pass, nick);
	}
	catch (const std::system_error& e)
	{
		std::cerr << SYSERR << e.what() << '\n';
		return ;
	}
	while (true)
	{
		try
		{
			char		buffer[2048];
			std::string	message;
			std::string	command;

			std::memset(buffer, 0, sizeof(buffer));
			if (recv(this->_fd, buffer, sizeof(buffer), 0) > 0)
			{
				message = buffer;
				std::size_t pos = message.find(PRIVMSG);
				if(pos != std::string::npos)
				{
					std::string nick = get_nick_from_privmsg(message);
					for (int i = 0; i < 8; i++)
					{
						sleep(2);
						send_message(this->_fd, answer[i], nick);
					}
				}
			}
			else
				throw std::system_error(errno, std::system_category(), ERR_FAILEDRECV);
		}
		catch(const std::exception& e)
		{
			std::cerr << SYSERR << e.what() << '\n';
			return ;
		}
	}
}

// "We're no strangers to love\nYou know the rules and so do I (do I)\nA full commitment's what I'm thinking of\nYou wouldn't get this from any other guy\nI just wanna tell you how I'm feeling\nGotta make you understand\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\nWe've known each other for so long\nYour heart's been aching, but you're too shy to say it (say it)\nInside, we both know what's been going on (going on)\nWe know the game and we're gonna play it\nAnd if you ask me how I'm feeling\nDon't tell me you're too blind to see\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\nWe've known each other for so long\nYour heart's been aching, but you're too shy to say it (to say it)\nInside, we both know what's been going on (going on)\nWe know the game and we're gonna play it\nI just wanna tell you how I'm feeling\nGotta make you understand\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you\nNever gonna give you up\nNever gonna let you down\nNever gonna run around and desert you\nNever gonna make you cry\nNever gonna say goodbye\nNever gonna tell a lie and hurt you