/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 20:19:14 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/23 18:58:46 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Client.hpp"

#define HOST "127.0.0.1"
#define SERVERNAME "BTC"

#define REPLY_MESSAGE(x) (std::string(":") + SERVERNAME + " " + x + "\r\n")
#define ERR_REPLY(code, client, middle, message) (REPLY_MESSAGE(code + " " + (std::string(client->getNickname()) != "" ? (std::string(client->getNickname()) + " ") : "") + (std::string(middle) != "" ? (std::string(middle) + " ") : "") + ":" + message))
#define BASIC_REPLY(cmd, middle, message) (REPLY_MESSAGE(cmd + " " + middle + " :" + message))
#define CMD_REPLY(client, cmd, middle, message) (std::string(":") + client->getNickname() + "!" + client->getUsername() + "@" + HOST + " " + cmd + (std::string(middle) != "" ? (" " + std::string(middle)) : "") + " :" + message + "\r\n")

namespace	replies {
	/* ---------------------------------- BASIC --------------------------------- */
	std::string RPL_WELCOME(Client *client)
	{
		return (ERR_REPLY("001", client, "", "There is no second best."));
	}

	/* --------------------------------- ERRORS --------------------------------- */
	// Returned to indicate a failed attempt at registering a connection
	// for which a password was required and was either not given or incorrect.
	std::string ERR_PASSWDMISMATCH(Client *client)
	{
		return (ERR_REPLY("464", client, "", "Password incorrect"));
	}

	// Returned by the server to indicate that the client must be registered
	// before the server will allow it to be parsed in detail.
	std::string ERR_NOTREGISTERED(Client *client)
	{
		return (ERR_REPLY("451", client, "", "You have not registered"));
	}

	// Returned by the server by numerous commands to indicate to the client
	// that it didn't supply enough parameters.
	std::string ERR_NEEDMOREPARAMS(Client *client, std::string const &cmd)
	{
		return (ERR_REPLY("461", client, cmd, "Not enough parameters"));
	}

	// Returned by the server to any link which tries to change part of the
	// registered details (such as password or user details from second USER message).
	std::string ERR_ALREADYREGISTRED(Client *client)
	{
		return (ERR_REPLY("462", client, " ", "You may not reregister"));
	}

	// Used to indicate the nickname parameter supplied to a command is currently unused.
	std::string ERR_NOSUCHNICK(Client *client, std::string const &channel_name)
	{
		return (ERR_REPLY("401", client, channel_name, "No such nick/channel"));
	}

	// Used to indicate the given channel name is invalid.
    std::string ERR_NOSUCHCHANNEL(Client *client, const std::string channel_name)
    {
		return (ERR_REPLY("403", client, channel_name, "No such channel"));
    }

	// Returned by the server whenever a client tries to perform a channel
	// effecting command for which the client isn't a member.
    std::string ERR_NOTONCHANNEL(Client *client, const std::string channel_name)
    {
		return (ERR_REPLY("442", client, channel_name, "You're not on that channel"));
    }

	// Returned by the server to indicate that the target user of the
	// command is not on the given channel.
    std::string ERR_USERNOTINCHANNEL(Client *client, const std::string channel_name)
    {
		return (ERR_REPLY("441", client, channel_name, "They aren't on that channel"));
    }

	// Any command requiring 'chanop' privileges (such as MODE messages) must
	// return this error if the client making the attempt is not a chanop on the specified channel.
    std::string ERR_CHANOPRIVSNEEDED(Client *client, const std::string channel_name)
    {
		return (ERR_REPLY("482", client, channel_name, "You're not channel operator"));
    }

	// Returned when a client tries to invite a user to a channel they are already on.
    std::string ERR_USERONCHANNEL(Client *client, Client *other, const std::string channel_name)
    {
		return (ERR_REPLY("443", client, other->getNickname() + " " + channel_name, "is already on channel"));
    }

    std::string ERR_KEYSET(Client *client, const std::string channel_name)
    {
		return (ERR_REPLY("467", client, channel_name, "Channel key already set"));
    }

	/* ------------------------------- CAP_COMMAND ------------------------------ */
	std::string RPL_CAP(void)
	{
		return (BASIC_REPLY("CAP", "* LS", "cap reply..."));
	}

	/* ------------------------------ PING_COMMAND ------------------------------ */
	std::string RPL_PING(std::string const &token)
	{
		return (BASIC_REPLY("PONG", SERVERNAME, token));
	}

	/* ------------------------------ NICK_COMMAND ------------------------------ */
	// Returned when a NICK message is processed that results in an attempt to
	// change to a currently existing nickname.
	std::string ERR_NICKNAMEINUSE(Client *client, std::string const &nick)
	{
		return (ERR_REPLY("433", client, nick, "Nickname is already in use"));
	}
	// Returned when a nickname parameter expected for a command and isn't found.
	std::string ERR_NONICKNAMEGIVEN(Client *client)
	{
		return (ERR_REPLY("431", client, "", "No nickname given"));
	}
	// Returned after receiving a NICK message which contains characters
	// which do not fall in the defined set. See section x.x.x for details on valid nicknames.
    std::string ERR_ERRONEUSNICKNAME(Client *client, std::string const &nick)
    {
		return (ERR_REPLY("432", client, nick, "Erroneus nickname"));
    }

	/* ------------------------------ QUIT_COMMAND ------------------------------ */
	std::string RPL_QUIT(Client *client, std::string const &msg)
	{
		return (CMD_REPLY(client, "QUIT", "", msg));
	}

	/* ----------------------------- PRIVMSG_COMMAND ---------------------------- */
	std::string	RPL_PRIVMSG(Client *client, std::string const &target, std::string const &msg)
	{
		return (CMD_REPLY(client, "PRIVMSG", target, msg));
	}

	std::string ERR_CANNOTSENDTOCHAN(Client *client, std::string const &channel_name)
	{
		return (ERR_REPLY("404", client, channel_name, "Cannot send to channel"));
	}

	/* ------------------------------ JOIN_COMMAND ------------------------------ */
	std::string RPL_JOIN(Client *client, std::string const &channel_name)
	{
		return (CMD_REPLY(client, "JOIN", channel_name + " *", client->getUsername()));
	}

	std::string ERR_CHANNELISFULL(Client *client, std::string const &channel_name)
	{
		return (ERR_REPLY("471", client, channel_name, "Cannot join channel (+l)"));
	}

	std::string ERR_INVITEONLYCHAN(Client *client, std::string const &channel_name)
	{
		return (ERR_REPLY("473", client, channel_name, "Cannot join channel (+i)"));
	}

	std::string RPL_NAMREPLY(Client *client, std::string const &channel_name, std::string const &names_list)
	{
		return (ERR_REPLY("353", client, "= " + channel_name, names_list));
	}

	std::string RPL_ENDOFNAMES(Client *client, std::string const &channel_name)
	{
		return (ERR_REPLY("366", client, channel_name, "End of /NAMES list"));
	}

	/* ------------------------------ PART_COMMAND ------------------------------ */
	std::string RPL_PART(Client *client, std::string const &channel_name, const std::string reason)
	{
		return (CMD_REPLY(client, "PART", channel_name, reason));
	}

    /* ------------------------------ TOPIC_COMMAND ----------------------------- */
	std::string RPL_TOPIC(Client *client, const std::string& channel_name, const std::string& topic)
	{
		return (ERR_REPLY("332", client, channel_name, topic));
	}

	std::string RPL_TOPICCHANGE(Client *client, const std::string& channel_name, const std::string& topic)
	{
		return (CMD_REPLY(client, "TOPIC", channel_name, topic));
	}

	std::string RPL_NOTOPIC(Client *client, const std::string& channel_name)
	{
		return (ERR_REPLY("331", client, channel_name, "No topic is set"));
	}

    /* ------------------------------ INVITE_COMMAND ----------------------------- */
    std::string RPL_INVITE(Client *client, std::string const &channel_name, std::string const &target)
    {
		return (CMD_REPLY(client, "INVITE", target, channel_name));
    }

	/* ------------------------------ KICK_COMMAND ------------------------------ */
	std::string RPL_KICK(Client *client, std::string const &channel_name, std::string const &target, const std::string reason)
	{
		return (CMD_REPLY(client, "KICK", channel_name + " " + target, reason));
	}

    /* ------------------------------- MODE_COMMAND ------------------------------ */
    std::string RPL_CHANNELMODEIS(Client *client, std::string const &channel_name, std::string const &modes)
	{
		return (ERR_REPLY("324", client, channel_name, modes));
	}

    std::string ERR_UMODEUNKNOWNFLAG(Client *client)
    {
		return (ERR_REPLY("501", client, "", "Unknown MODE flag"));
    }

	std::string ERR_BADCHANNELKEY(Client *client, std::string const &channel_name)
	{
		return (ERR_REPLY("475", client, channel_name, "Invalid channel key"));
	}

    std::string ERR_TOOMANYARGS(Client *client, const char mode)
    {
		return (ERR_REPLY("420", client, std::string(1, mode), "Too many arguments"));
    }

    std::string RPL_SETMODECLIENT(Client* client, std::string const &channel_name, std::string const &mode, std::string const &target)
    {
		return (CMD_REPLY(client, "MODE", channel_name + " " + mode, target));
    }
};
