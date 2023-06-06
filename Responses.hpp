/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responses.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:13:03 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/06/05 20:19:07 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

namespace	replies
{
	/* -------------------------------------------------------------------------- */
	/*                                    ERROR                                   */
	/* -------------------------------------------------------------------------- */

	// @note add print statements for the server side later
	// and the servername (either macro or var inside the server)
	// also: check whether the parameters are even used in the functions!

	std::string ERR_ALREADYREGISTRED(void)
	{
		std::cout << "User(name)" << " is already registered" << std::endl;
		return std::string(":") + "Servername" + " 462 " ":Already registered in\r\n";
	}

	std::string ERR_NOTREGISTERED(const std::string& cmd)
	{
		std::cout << "User(name)" << " is not registered" << std::endl;
		return std::string(":") + "Servername" + " 451 " + ":You have not registered\r\n";
	}

	std::string ERR_PASSWDMISMATCH(void)
	{
		std::cout << "Incorrect password" << std::endl;
		return std::string(":") + "Servername" + " 464 " + "PASS" + ":Password incorrect\r\n";
	}

	std::string ERR_NEEDMOREPARAMS(const std::string& cmd)
	{
		std::cout << "Not enough parameters provided" << std::endl;
		return std::string(":") + "Servername" + " 461 " + cmd + ":Not enough parameters\r\n";
	}

	std::string ERR_USERSDONTMATCH(const std::string& nick, const std::string& target)
	{
		std::cout << "You cannot change modes for other users" << std::endl;
		return std::string(":") + "Servername" + " 502 " + nick + " :Cannot change mode for other users\r\n";
	}

	std::string ERR_NICKNAMEINUSE(const std::string& nick)
	{
		std::cout << "Nickname" << " is already in use" << std::endl;
		return std::string(":") + "Servername" + " 433 " + nick + " :Nickname is already in use\r\n";
	}

	std::string ERR_NOSUCHNICK(const std::string& nick, const std::string channel_name)
	{
		std::cout << "Nickname/Username" << " : No such nick/channel" << std::endl;
		return std::string(":") + "Servername" + " 401 " + nick + " " + channel_name + " :No such nick/channel\r\n";
	}

	std::string ERR_ERRONEUSNICKNAME(const std::string& nick, const std::string& wrong_nick)
	{
		std::cout << "Nick(name)" << " : Erroneous nickname" << std::endl;
		return std::string(":") + "Servername" + " 432 " + wrong_nick + " :Erroneous nickname\r\n";
	}

	std::string ERR_NONICKNAMEGIVEN(void)
	{
		std::cout << "Nickname not given" << std::endl;
		return std::string(":") + "Servername" + " 431 " + " :Nickname not given\r\n";
	}

	std::string ERR_CANNOTSENDTOCHAN(const std::string& nick, const std::string& channel_name)
	{
		std::cout << "Nick(name): " << "Nickname" << " : Cannot send to channel: " << "Channelname" << std::endl;
		return std::string(":") + "Servername" +  " 404 " + nick + " " + channel_name + " :Cannot send to channel\r\n";
	}

	std::string ERR_USERNOTINCHANNEL(const std::string& nick, const std::string& channel_name)
	{
		std::cout << "Nick(name)" << " : Not in channel: " << "Channelname" << std::endl;
		return std::string(":") + "441 " + "Servername" + " " + nick + " " + channel_name + " :is not on channel \r\n";
	}

	std::string ERR_USERONCHANNEL(const std::string& nick, const std::string& channel_name, const std::string& target)
	{
		std::cout << "Nick(name)" << " : Is already on channel: " << "Channelname" << std::endl;
		return std::string(":") + "Servername" + " 443 " + target + " " + channel_name + " :Is already on channel \r\n";
	}

	std::string ERR_NOTONCHANNEL(const std::string nick, const std::string channel_name)
	{
		std::cout << "You're not on that channel" << std::endl;
		return std::string(":") + "Servername" + " 401 " + nick + " " + channel_name + " :You're not on that channel \r\n";
	}

	std::string ERR_INVITEONLYCHAN(const std::string& nick, const std::string& channel_name)
	{
		std::cout << "Cannot join channel: " << "Invite only" << std::endl;
		return std::string(":") + "Servername" + " 473 " + nick + " " + channel_name + " :Cannot join channel (+i) - you must be invited\r\n";
	}

	std::string ERR_CHANOPRIVSNEEDED(const std::string& nick, const std::string& channel_name)
	{
		std::cout << "You're not a channel operator" << std::endl;
		return std::string(":") + "Servername" + " 482 " + channel_name + " :You're not a channel operator \r\n";
	}

	std::string ERR_NOPRIVILEGES(const std::string& nick, const std::string& cmd)
	{
		std::cout << "Permission Denied - You're not an IRC operator" << std::endl;
		return std::string(":") + "Servername" + " 481 " + cmd + " :Permission Denied - You're not an IRC operator\r\n";
	}

	std::string ERR_NOSUCHCHANNEL(const std::string& nick, const std::string& channel_name)
	{
		std::cout << "Channelname" << ": No such channel" << std::endl;
		return std::string(":") + "Servername" + " 403 " + channel_name + " :No such channel\r\n";
	}

	std::string ERR_UNKNOWNCOMMAND(const std::string& nick, const std::string& cmd)
	{
		std::cout << cmd << ": Unknown command" << std::endl;
		return std::string(":") + "Servername" + " 421 " + cmd + " :Unknown command\r\n";
	}

	std::string ERR_UMODEUNKNOWNFLAG(void)
	{
		std::cout << "Unknown MODE flags" << std::endl;
		return std::string(":") + "Servername" + " 501 " + " :Unknown MODE flags\r\n";
	}

	/* -------------------------------------------------------------------------- */
	/*                                   COMMAND                                  */
	/* -------------------------------------------------------------------------- */

	std::string RPL_CAP()
	{
		std::cout << "Server capabilities sent to client" << std::endl;
		return std::string(":") + "Servername" + " CAP * LS :cap reply...\r\n";
	}

	std::string RPL_PING(const std::string& nick, const std::string& token)
	{
		std::cout << nick << " says: PING" << std::endl;
		return std::string(":") + "Servername" + " PONG " + "Servername" + " :" + token + "\r\n";
	}

	std::string RPL_JOIN(const std::string& nick, const std::string& user, const std::string& channel_name)
	{
		std::cout << nick << ": joined the channel " << channel_name << std::endl;
		return std::string(":") + nick + "!" + user + "@" + HOST + " JOIN " + channel_name + " * :" + user + "\r\n";
	}

	std::string RPL_PART(const std::string& nick, const std::string& user, const std::string& channel_name, const std::string reason)
	{
		std::cout << nick << ": left the channel " << channel_name << std::endl;
		return std::string(":") + nick + "!" + user + "@" + HOST + " PART " + channel_name + " " + reason + "!" +  "\r\n";
	}

	std::string RPL_NICKCHANGE(const std::string& old_nick, const std::string& new_nick, const std::string& user)
	{
		std::cout << old_nick << ": changed his nick to: " << new_nick << std::endl;
		return std::string(":") + old_nick + "!" + user + "@" + HOST + " " + "NICK" + " :" + new_nick + "\r\n";
	}

	std::string	RPL_PRIVMSG(const std::string& nick, const std::string& user, const std::string& target, const std::string& msg)
	{
		std::cout << nick << ": sent message:  " << msg << "to " << target << std::endl;
		return std::string(":") + nick + "!" + user + "@" + HOST + " PRIVMSG " + target + " :" + msg + "\r\n";
	}

	std::string RPL_SETMODECLIENT(const std::string& nick, const std::string& user, const std::string& channel_name, const std::string& mode, const std::string& target)
	{
		std::cout << nick << ": changed mode of  " << target << " to: " << mode << std::endl;
		return std::string(":") + nick + "!" + user + "@" + HOST + " MODE " + channel_name + " " + mode + " " + target + "\r\n";
	}

	std::string RPL_TOPICCHANGE(const std::string& nick, const std::string& user, const std::string& channel_name, const std::string& topic)
	{
		std::cout << nick << ": changed topic of  " << channel_name << " to: " << topic << std::endl;
		return std::string(":") + nick + "!" + user + "@" + HOST + " TOPIC " + channel_name + " :" + topic + "\r\n";
	}

	std::string	RPL_INVITED(const std::string& nick, const std::string& user, const std::string& channel_name, const std::string& target)
	{
		std::cout << nick << ": invited  " << target << " to: " << channel_name << std::endl;
		return std::string(":") + nick + "!" + user + "@" + HOST + " INVITE " + target + " :" + channel_name + "\r\n";
	}

	std::string RPL_KICK(const std::string& nick, const std::string& user, const std::string& channel_name, const std::string& target, const std::string reason)
	{
		std::cout << nick << ": kicked  " << target << " out of: " << channel_name << std::endl;
		return std::string(":") +  nick + "!" + user + "@" + HOST + " KICK " + channel_name + " " + target + " :" + reason + "\r\n";
	}

	std::string RPL_QUIT(const std::string& nick, const std::string& user)
	{
		std::cout << nick << ": left the server" << std::endl;
		return std::string(":") + nick + "!" + user + "@" + HOST + " " + "QUIT :" + "Tschö!" + "\r\n";
	}

	std::string RPL_BOT(const std::string& nick, const std::string& channel_name, const std::string& msg)
	{
		// @note here some bot stuff later on
	}

	/* -------------------------------------------------------------------------- */
	/*                                   NUMERIC                                  */
	/* -------------------------------------------------------------------------- */

	// @note do I need to provide server print messages here as well?

	std::string RPL_WELCOME(const std::string& nick, const std::string user)
	{
		return std::string(":") + "Servername" + " 001 " + nick + " :Welcome to the BTC network, " + nick + "!" + user + "@" + HOST + "\r\n";
	}

	std::string RPL_MODEUSER(const std::string& nick, const std::string& mode)
	{
		return std::string(":") + "Servername" + " 221 " + nick + " " + mode + "\r\n";
	}

	std::string RPL_SETMODECHANNEL(const std::string& nick, const std::string& channel_name, const std::string& mode)
	{
		return std::string(":") + "Servername" + " 324 " + nick + " " + channel_name + " " + mode + "\r\n";
	}

	std::string RPL_CHANNELMODEIS(const std::string& nick, const std::string& channel_name, const std::string& mode)
	{
		return std::string(":") + "Servername" + " 324 " + nick + " " + channel_name + " " + mode + "\r\n";
	}

	std::string RPL_NAMREPLY(const std::string& nick, const std::string& channel_name, const std::string& names_list)
	{
		return std::string(":") + "Servername" + " 353 " + nick + " = " + channel_name + " :" +  names_list + "\r\n";
	}

	std::string RPL_ENDOFNAMES(const std::string& nick, const std::string& channel_name)
	{
		return std::string(":")  + "Servername" + " 366 " + nick + " " + channel_name + " :END of NAMES list\r\n";
	}

	std::string RPL_YOUREOPER(const std::string& nick, const std::string& target)
	{
		return std::string(":") + "Servername" + " 381 " + "PASS :You are now an IRC operator\r\n";
	}

	std::string	RPL_INVITING(const std::string& nick, const std::string& channel_name, const std::string& target)
	{
		return std::string(":") + "Servername" + " 341 " + nick + " " + target + " " + channel_name + "\r\n";
	}

	std::string RPL_TOPIC(const std::string& nick, const std::string& channel_name, const std::string& topic)
	{
		return std::string(":") + "Servername" + " 332 " + nick + " " + channel_name + " :" + topic + "\r\n";
	}

	std::string RPL_NOTOPIC(const std::string& nick, const std::string& channel_name)
	{
		return std::string(":") + "Servername" + " 331 " + nick + " " + channel_name + " :No topic is set\r\n";
	}

}
