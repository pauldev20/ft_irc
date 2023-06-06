
#include "irc.hpp"
#include "Message.hpp"

#include <string>
#include <algorithm> // std::all_of
#include <cctype> // std::isdigit, std::isalpha
#include <cstring> // strlen

#define MESSAGE_MAX 512
#define DELIM ' '
#define CRLF "\r\n"
#define COLON ':'

/*
BNF for IRC messages:
<message>  ::= [':' <prefix> ' ' ] <command> <params> <crlf>
<prefix>   ::= <servername> | <nick> [ '!' <user> ] [ '@' <host> ]
<command>  ::= <letter> { <letter> } | <number> <number> <number>
<params>   ::= [ ':' <trailing> | <middle> <params> ]

<middle>   ::= <Any *non-empty* sequence of octets not including SPACE
               or NUL or CR or LF, the first of which may not be ':'>
<trailing> ::= <Any, possibly *empty*, sequence of octets not including
                 NUL or CR or LF>

<crlf>     ::= CR LF (/r/n)
*/

static bool	is_all_digit(const std::string& str)
{
	for (std::string::const_iterator i = str.begin(), j = str.end(); i != j; i++)
		if (!isdigit(*i))
			return false;
	return true;
}

static bool	is_all_alpha(const std::string& str)
{
	for (std::string::const_iterator i = str.begin(), j = str.end(); i != j; i++)
		if (!isalpha(*i))
			return false;
	return true;
}

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

static void	handlePrefix(Message& Message, std::string& message)
{
	if (message[0] == COLON)
		Message.setPrefix(getNextToken(message));
}

static int	handleMessage(Message& Message, std::string& message)
{
	std::string token = getNextToken(message);

	if (token.empty())
		return (ERROR);
	if (!is_all_alpha(token) && !is_all_digit(token))
		return (ERROR);
	if (token == CMD_CAP)
		Message.setId(ID_CAP);
	else if (token == CMD_PING)
		Message.setId(ID_PING);
	else if (token == CMD_PASS)
		Message.setId(ID_PASS);
	else if (token == CMD_NICK)
		Message.setId(ID_NICK);
	else if (token == CMD_USER)
		Message.setId(ID_USER);
	else if (token == CMD_QUIT)
		Message.setId(ID_QUIT);
	else if (token == CMD_PRIVMSG)
		Message.setId(ID_PRIVMSG);
	else if (token == CMD_JOIN)
		Message.setId(ID_JOIN);
	else if (token == CMD_PART)
		Message.setId(ID_PART);
	else
	{
		std::cout << "ERROR: Unknown command: " << token << std::endl;
		return (ERROR);
	}
	return (SUCCESS);
}

static int	handleParams(Message& Message, std::string& message)
{
	std::string	token;

	for (int i = 0; i < PARAM_MAX; i++)
	{
		if (message[0] == COLON)
			i = PARAM_MAX;
		token = getNextToken(message);
		if (token.empty())
			break ;
		Message.addParam(token);
	}
	return (SUCCESS);
}

int	irc::parseMessage(Message& message, std::string& msg)
{
	if (msg.find(CRLF) == std::string::npos)
		return (ERROR);
	if (msg.find(CRLF) > MESSAGE_MAX)
		return (ERROR);

	handlePrefix(message, msg);
	if (handleMessage(message, msg) == ERROR)
		return (ERROR);
	if (handleParams(message, msg) == ERROR)
		return (ERROR);
	if (msg.substr(0, strlen(CRLF)) != CRLF)
		return (ERROR);
	return (SUCCESS);
}