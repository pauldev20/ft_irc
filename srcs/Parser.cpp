/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 07:35:59 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/11 07:36:00 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "Message.hpp"
#include "cmds/Commands.hpp"

#include <string>
#include <algorithm> // std::all_of
#include <cctype> // std::isdigit, std::isalpha
#include <cstring> // strlen

#define DELIM ' '
#define CRLF "\r\n"
#define CR '\r'
#define LF '\n'
#define COLON ':'

#define CMD_CAP "CAP"
#define CMD_NICK "NICK"
#define CMD_USER "USER"
#define CMD_QUIT "QUIT"
#define CMD_JOIN "JOIN"
#define CMD_PART "PART"
#define CMD_PRIVMSG "PRIVMSG"
#define CMD_PASS "PASS"
#define CMD_KICK "KICK"
#define CMD_INVITE "INVITE"
#define CMD_TOPIC "TOPIC"
#define CMD_MODE "MODE"
#define CMD_PING "PING"

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
	for (std::string::const_iterator i = str.begin(), j = str.end(); i != j; ++i)
	{
		if (!isdigit(*i))
			return false;
	}
	return true;
}

static bool	is_all_alpha(const std::string& str)
{
	for (std::string::const_iterator i = str.begin(), j = str.end(); i != j; ++i)
	{
		if (!isalpha(*i))
			return false;
	}
	return true;
}

static	std::string get_next_token(std::string& message, bool isTrailing)
{
	std::string token;

	if (isTrailing == true)
		message.erase(0, 1);
	if (isTrailing == true
		|| message.find(DELIM) == std::string::npos
		|| message.find(DELIM) > message.find(CRLF))
	{
		token = message.substr(0, message.find(CRLF));
		message.erase(0, message.find(CRLF));
	}
	else
	{
		token = message.substr(0, message.find(DELIM));
		message.erase(0, message.find(DELIM) + 1);
	}
	return (token);
}

static void	handle_prefix(Message& command, std::string& message)
{
	if (message[0] == COLON)
	{
		message.erase(0, 1);
		command.setPrefix(get_next_token(message, false));
	}
}

static int	handle_command(Message& command, std::string& message)
{
	std::string token = get_next_token(message, false);

	if (token.empty())
		return (ERROR);
	if (!is_all_alpha(token) && !is_all_digit(token))
		return (ERROR);
	if (token == CMD_CAP)
	{
		static CAP cap;
		command.setCmdAll(&cap, CMD_CAP);
	}
	else if (token == CMD_PING)
	{
		static PING ping;
		command.setCmdAll(&ping, CMD_PING);
	}
	else if (token == CMD_PASS)
	{
		static PASS pass;
		command.setCmdAll(&pass, CMD_PASS);
	}
	else if (token == CMD_NICK)
	{
		static NICK nick;
		command.setCmdAll(&nick, CMD_NICK);
	}
	else if (token == CMD_USER)
	{
		static USER user;
		command.setCmdAll(&user, CMD_USER);
	}
	else if (token == CMD_PRIVMSG)
	{
		static PRIVMSG privmsg;
		command.setCmdAll(&privmsg, CMD_PRIVMSG);
	}
	else if (token == CMD_JOIN)
	{
		static JOIN join;
		command.setCmdAll(&join, CMD_JOIN);
	}
	else if (token == CMD_PART)
	{
		static PART part;
		command.setCmdAll(&part, CMD_PART);
	}
	else if (token == CMD_QUIT)
	{
		static QUIT quit;
		command.setCmdAll(&quit, CMD_QUIT);
	}
	else if (token == CMD_KICK)
	{
		static KICK kick;
		command.setCmdAll(&kick, CMD_KICK);
	}
    else if (token == CMD_TOPIC)
	{
		static TOPIC topic;
		command.setCmdAll(&topic, CMD_TOPIC);
	}
	else if (token == CMD_INVITE)
	{
		static INVITE invite;
		command.setCmdAll(&invite, CMD_INVITE);
	}
	else if (token == CMD_MODE)
	{
		static MODE mode;
		command.setCmdAll(&mode, CMD_MODE);
	}
	else
		return (ERROR);
	return (SUCCESS);
}

static int	handle_params(Message& command, std::string& message)
{
	std::string	token;

	for (int i = 0; i < PARAM_MAX; i++)
	{
		if (message[0] == COLON)
		{
			command.setHasTrailing(true);
			token = get_next_token(message, true);
			command.setTrailing(token);
			return (SUCCESS);
		}
		else
			token = get_next_token(message, false);
		command.addParam(token);
	}
	return (SUCCESS);
}

int	irc::parse_message(Message& command, std::string& message)
{
	if (message.find(CRLF) == std::string::npos)
		return (ERROR);

	handle_prefix(command, message);
	if (handle_command(command, message) == ERROR)
		return (ERROR);
	if (handle_params(command, message) == ERROR)
		return (ERROR);
	if (message.substr(0, strlen(CRLF)) != CRLF)
		return (ERROR);
	return (SUCCESS);
}