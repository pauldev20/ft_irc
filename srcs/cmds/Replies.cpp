/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 20:19:14 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/06 13:26:23 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#define SERVER "127.0.0.1"

namespace	replies {
	/* ---------------------------------- BASIC --------------------------------- */
	std::string RPL_WELCOME(const std::string& nick, const std::string user)
	{
		return std::string(":") + SERVER + " 001 " + nick + " :Welcome to the BTC network, " + nick + "!" + user + "@" + SERVER + "\r\n";
	}

	/* --------------------------------- ERRORS --------------------------------- */
	// Returned to indicate a failed attempt at registering a connection for which a password was required and was either not given or incorrect.
	std::string ERR_PASSWDMISMATCH(void)
	{
		return std::string(":") + SERVER + " 464 " + "PASS" + ":Password incorrect\r\n";
	}

	// Returned by the server to indicate that the client must be registered before the server will allow it to be parsed in detail.
	std::string ERR_NOTREGISTERED(void)
	{
		return std::string(":") + SERVER + " 451 " + ":You have not registered\r\n";
	}

	// Returned by the server by numerous commands to indicate to the client that it didn't supply enough parameters.
	std::string ERR_NEEDMOREPARAMS(const std::string& cmd)
	{
		return std::string(":") + SERVER + " 461 " + cmd + ":Not enough parameters\r\n";
	}

	// Returned by the server to any link which tries to change part of the registered details (such as password or user details from second USER message).
	std::string ERR_ALREADYREGISTRED(void)
	{
		return std::string(":") + SERVER + " 462 " ":Already registered in\r\n";
	}

	std::string ERR_NOSUCHNICK(const std::string& nick, const std::string channel_name)
	{
		return std::string(":") + "Servername" + " 401 " + nick + " " + channel_name + " :No such nick/channel\r\n";
	}

    std::string ERR_NOSUCHCHANNEL(const std::string& nick, const std::string channel_name)
    {
        return std::string(":") + "Servername" + " 403 " + nick + " " + channel_name + " :No such channel\r\n";
    }

    std::string ERR_NOTONCHANNEL(const std::string& nick, const std::string channel_name)
    {
        return std::string(":") + "Servername" + " 442 " + nick + " " + channel_name + " :You're not on that channel\r\n";
    }

    std::string ERR_USERNOTINCHANNEL(const std::string& nick, const std::string channel_name)
    {
        return std::string(":") + "Servername" + " 441 " + nick + " " + channel_name + " :They aren't on that channel\r\n";
    }

    std::string ERR_CHANOPRIVSNEEDED(const std::string& nick, const std::string channel_name)
    {
        return std::string(":") + "Servername" + " 482 " + nick + " " + channel_name + " :You're not channel operator\r\n";
    }

    std::string ERR_USERONCHANNEL(const std::string& nick, const std::string channel_name)
    {
        return std::string(":") + "Servername" + " 443 " + nick + " " + channel_name + " :is already on channel\r\n";
    }

	/* ------------------------------- CAP_COMMAND ------------------------------ */
	std::string RPL_CAP(void) {
		// std::cout << "RPL_CAP sent to Client" << std::endl; //@todo make debug
		return (std::string(":") + SERVER + " CAP * LS :cap reply...\r\n");
	}

	/* ------------------------------ PING_COMMAND ------------------------------ */
	std::string RPL_PING(const std::string& token)
	{
		return std::string(":") + SERVER + " PONG " + SERVER + " :" + token + "\r\n";
	}

	/* ------------------------------ NICK_COMMAND ------------------------------ */
	std::string ERR_NICKNAMEINUSE(const std::string& nick)
	{
		return std::string(":") + "Servername" + " 433 " + nick + " :Nickname is already in use\r\n";
	}
	std::string ERR_NONICKNAMEGIVEN(void)
	{
		return std::string(":") + "Servername" + " 431 " + " :Nickname not given\r\n";
	}
    std::string ERR_ERRONEUSNICKNAME(const std::string& nick)
    {
        return std::string(":") + "Servername" + " 432 " + nick + " :Erroneus nickname\r\n";
    }
	std::string RPL_NICKCHANGE(const std::string& old_nick, const std::string& new_nick, const std::string& user)
	{
		return std::string(":") + old_nick + "!" + user + "@" + SERVER + " " + "NICK" + " :" + new_nick + "\r\n";
	}

	/* ------------------------------ QUIT_COMMAND ------------------------------ */
	std::string RPL_QUIT(const std::string& nick, const std::string& user)
	{
		return std::string(":") + nick + "!" + user + "@" + SERVER + " " + "QUIT :" + "Tschö!" + "\r\n";
	}

	/* ----------------------------- PRIVMSG_COMMAND ---------------------------- */
	std::string	RPL_PRIVMSG(const std::string& nick, const std::string& user, const std::string& target, const std::string& msg)
	{
		return std::string(":") + nick + "!" + user + "@" + SERVER + " PRIVMSG " + target + " :" + msg + "\r\n";
	}

	std::string ERR_CANNOTSENDTOCHAN(const std::string& nick, const std::string& channel_name)
	{
		return std::string(":") + "Servername" +  " 404 " + nick + " " + channel_name + " :Cannot send to channel\r\n";
	}

	/* ------------------------------ JOIN_COMMAND ------------------------------ */
	std::string RPL_JOIN(const std::string& nick, const std::string& user, const std::string& channel_name)
	{
		return std::string(":") + nick + "!" + user + "@" + SERVER + " JOIN " + channel_name + " * :" + user + "\r\n";
	}

	std::string ERR_CHANNELISFULL(const std::string& nick, const std::string& channel_name)
	{
		return std::string(":") + SERVER + " 471 " + nick + " " + channel_name + " :Cannot join channel (+l)\r\n";
	}

	std::string ERR_INVITEONLYCHAN(const std::string& nick, const std::string& channel_name)
	{
		return std::string(":") + SERVER + " 473 " + nick + " " + channel_name + " :Cannot join channel (+i)\r\n";
	}
    
	std::string ERR_BANNEDFROMCHAN(const std::string& nick, const std::string& channel_name)
	{
		return std::string(":") + SERVER + " 474 " + nick + " " + channel_name + " :Cannot join channel (+b)\r\n";
	}

	/* ------------------------------ PART_COMMAND ------------------------------ */
	std::string RPL_PART(const std::string& nick, const std::string& user, const std::string& channel_name, const std::string reason)
	{
		return std::string(":") + nick + "!" + user + "@" + SERVER + " PART " + channel_name + " " + reason + "!" +  "\r\n";
	}

    /* ------------------------------ TOPIC_COMMAND ----------------------------- */
    // @note copilots suggestions. let's see if it works!
    std::string RPL_TOPIC(const std::string& nick, const std::string& user, const std::string& channel_name, const std::string& topic)
    {
        return std::string(":") + nick + "!" + user + "@" + SERVER + " TOPIC " + channel_name + " :" + topic + "\r\n";
    }

    std::string RPL_NOTOPIC(const std::string& nick, const std::string& user, const std::string& channel_name)
    {
        return std::string(":") + nick + "!" + user + "@" + SERVER + " TOPIC " + channel_name + " :No topic is set\r\n";
    }

    /* ------------------------------ INVITE_COMMAND ----------------------------- */
    std::string RPL_INVITE(const std::string& nick, const std::string& user, const std::string& channel_name, const std::string& target)
    {
        return std::string(":") + nick + "!" + user + "@" + SERVER + " INVITE " + target + " " + channel_name + "\r\n";
    }
};
