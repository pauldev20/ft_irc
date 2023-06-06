
#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>

#define ERROR -1
#define SUCCESS 0
#define PARAM_MAX 15

#define CMD_CAP "CAP"
#define CMD_PING "PING"
#define CMD_PASS "PASS"
#define CMD_NICK "NICK"
#define CMD_USER "USER"
#define CMD_QUIT "QUIT"
#define CMD_PRIVMSG "PRIVMSG"

enum MessageID
{
	ID_CAP,
	ID_PING,
	ID_PASS,
	ID_NICK,
	ID_USER,
	ID_QUIT,
	ID_PRIVMSG
};

class Message
{
	private:
		std::string						_prefix; // @note potentially separate object / more complex, also the prefix doesn't belong to the command
		int								_id;
		std::vector<std::string>		_params;
	public:		
										Message();
										Message(std::string prefix, int id, std::vector<std::string> params);
										~Message();
		void							setPrefix(std::string prefix);
		void							setId(int id);
		void							addParam(std::string param);
		void							setParams(std::vector<std::string> params);
		const std::string&				getPrefix() const;
		const int&						getId() const;
		const std::vector<std::string>&	getParams() const;
};

#endif