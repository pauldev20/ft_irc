
#include "Command.hpp"

#include <string>
#include <algorithm> // std::all_of
#include <cctype> // std::isdigit, std::isalpha

#define MESSAGE_MAX 512
#define DELIM ' '
#define CRLF "\r\n"
#define COLON ':'

static	std::string getNextToken(std::string& message)
{
	std::string token;

	if (message.find(DELIM) == std::string::npos
		|| message.find(DELIM) > message.find(CRLF))
	{
		token = message.substr(0, message.find(CRLF));
		message.erase(0, message.find(CRLF));
		return (token);
	}
	else
	{
		token = message.substr(0, message.find(DELIM));
		message.erase(0, message.find(DELIM) + 1);
	}
	return (token);
}

static void	handlePrefix(Command& command, std::string& message)
{
	if (message[0] == COLON)
		command.setPrefix(getNextToken(message));
}

static int	handleCommand(Command& command, std::string& message)
{
	std::string token = getNextToken(message);

	if (token.empty())
		return (ERROR);
	if (!std::all_of(token.begin(), token.end(), std::isdigit)
		&& !std::all_of(token.begin(), token.end(), std::isalpha))
		return (ERROR);
	if (token == CMD_KICK)
		command.setId(ID_KICK);
	else if (token == CMD_INVITE)
		command.setId(ID_INVITE);
	else if (token == CMD_TOPIC)
		command.setId(ID_TOPIC);
	else if (token == CMD_MODE)
		command.setId(ID_MODE);
	else if (token == CMD_PING)
		command.setId(ID_PING);
	else
		return (ERROR);
	return (SUCCESS);
}

static int	handleParams(Command& command, std::string& message)
{
	std::string	token;

	for (int i = 0; i < PARAM_MAX; i++)
	{
		if (message[0] == COLON)
			i = PARAM_MAX;
		token = getNextToken(message);
		if (token.empty())
			break ;
		command.addParam(token);
	}
	return (SUCCESS);
}

int	parseMessage(Command& command, std::string& message)
{
	if (message.find(CRLF) == std::string::npos)
		return (ERROR);
	if (message.find(CRLF) > MESSAGE_MAX)
		return (ERROR);

	handlePrefix(command, message);
	if (handleCommand(command, message) == ERROR)
		return (ERROR);
	if (handleParams(command, message) == ERROR)
		return (ERROR);
	if (message.substr(0, strlen(CRLF)) != CRLF)
		return (ERROR);
	return (SUCCESS);
}