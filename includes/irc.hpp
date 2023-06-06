
#ifndef IRC_HPP
#define IRC_HPP

#include "Message.hpp"
#include "Server.hpp"

namespace debug
{
	void	debugMessage(const Message& message);
}

namespace irc
{
	int		parseMessage(Message& message, std::string& msg);
	int		executeMessage(Message& message, Server* server, Client* client);
}

namespace replies
{
	std::string RPL_WELCOME(const std::string& nick, const std::string user);
	std::string RPL_CAP(void);
	std::string ERR_PASSWDMISMATCH(void);
	std::string ERR_NOTREGISTERED(void);
	std::string ERR_NEEDMOREPARAMS(const std::string& cmd);
	std::string ERR_ALREADYREGISTRED(void);
	std::string ERR_NICKNAMEINUSE(const std::string& nick);
	std::string ERR_NONICKNAMEGIVEN(void);
	std::string RPL_NICKCHANGE(const std::string& old_nick, const std::string& new_nick, const std::string& user);
	std::string RPL_PING(const std::string& token);
	std::string RPL_QUIT(const std::string& nick, const std::string& user);
	std::string ERR_NOSUCHNICK(const std::string& nick, const std::string channel_name);
	std::string	RPL_PRIVMSG(const std::string& nick, const std::string& user, const std::string& target, const std::string& msg);
	std::string ERR_CANNOTSENDTOCHAN(const std::string& nick, const std::string& channel_name);
}

#endif
