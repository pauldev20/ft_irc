
#ifndef IRC_HPP
#define IRC_HPP

#include "Message.hpp"
#include "Server.hpp"

#define ERROR -1
#define SUCCESS 0
#define PARAM_MAX 15

namespace debug
{
	void	printMessage(const Message& message);
}

namespace irc
{
	int	parseMessage(Message& message, std::string& msg);
	int	executeMessage(Message& message, Server* server, Client* client);
}

namespace replies
{
	/* ---------------------------------- BASIC --------------------------------- */
	std::string RPL_WELCOME(Client *client);
	/* --------------------------------- ERRORS --------------------------------- */
	std::string ERR_PASSWDMISMATCH(Client *client);
	std::string ERR_NOTREGISTERED(Client *client);
	std::string ERR_NEEDMOREPARAMS(Client *client, std::string const &cmd);
	std::string ERR_ALREADYREGISTRED(Client *client);
	std::string ERR_NOSUCHNICK(Client *client, std::string const &channel_name);
	std::string ERR_NOSUCHCHANNEL(Client *client, const std::string channel_name);
	std::string ERR_NOTONCHANNEL(Client *client, const std::string channel_name);
	std::string ERR_USERNOTINCHANNEL(Client *client, const std::string channel_name);
	std::string ERR_CHANOPRIVSNEEDED(Client *client, const std::string channel_name);
	std::string ERR_USERONCHANNEL(Client *client, Client *other, const std::string channel_name);
	std::string ERR_KEYSET(Client *client, const std::string channel_name);
	/* ------------------------------- CAP_COMMAND ------------------------------ */
	std::string RPL_CAP(void);
	/* ------------------------------ PING_COMMAND ------------------------------ */
	std::string RPL_PING(std::string const &token);
	/* ------------------------------ NICK_COMMAND ------------------------------ */
	std::string ERR_NICKNAMEINUSE(Client *client, std::string const &nick);
	std::string ERR_NONICKNAMEGIVEN(Client *client);
    std::string ERR_ERRONEUSNICKNAME(Client *client, std::string const &nick);
	/* ------------------------------ QUIT_COMMAND ------------------------------ */
	std::string RPL_QUIT(Client *client, std::string const &msg);
	/* ----------------------------- PRIVMSG_COMMAND ---------------------------- */
	std::string	RPL_PRIVMSG(Client *client, std::string const &target, std::string const &msg);
	std::string ERR_CANNOTSENDTOCHAN(Client *client, std::string const &channel_name);
	/* ------------------------------ JOIN_COMMAND ------------------------------ */
	std::string RPL_JOIN(Client *client, std::string const &channel_name);
	std::string ERR_CHANNELISFULL(Client *client, std::string const &channel_name);
	std::string ERR_INVITEONLYCHAN(Client *client, std::string const &channel_name);
	std::string RPL_NAMREPLY(Client *client, std::string const &channel_name, std::string const &names_list);
	std::string RPL_ENDOFNAMES(Client *client, std::string const &channel_name);
	/* ------------------------------ PART_COMMAND ------------------------------ */
	std::string RPL_PART(Client *client, std::string const &channel_name, const std::string reason);
	/* ------------------------------ TOPIC_COMMAND ----------------------------- */
	std::string RPL_TOPIC(Client *client, const std::string& channel_name, const std::string& topic);
	std::string RPL_TOPICCHANGE(Client *client, const std::string& channel_name, const std::string& topic);
	std::string RPL_NOTOPIC(Client *client, const std::string& channel_name);
	/* ------------------------------ INVITE_COMMAND ----------------------------- */
    std::string RPL_INVITE(Client *client, std::string const &channel_name, std::string const &target);
	/* ------------------------------ KICK_COMMAND ------------------------------ */
	std::string RPL_KICK(Client *client, std::string const &channel_name, std::string const &target, const std::string reason);
	/* ------------------------------- MODE_COMMAND ------------------------------ */
    std::string RPL_CHANNELMODEIS(Client *client, std::string const &channel_name, std::string const &modes);
	std::string RPL_SETMODECHANNEL(Client *client, std::string const &channel_name, std::string const &mode);
	std::string ERR_UMODEUNKNOWNFLAG(Client *client);
	std::string ERR_TOOMANYARGS(Client *client, const char mode);
};

#endif
