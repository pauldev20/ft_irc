
#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>

#define CMD_KICK "KICK"
#define CMD_INVITE "INVITE"
#define CMD_TOPIC "TOPIC"
#define CMD_MODE "MODE"
#define CMD_PING "PING"

enum CommandID
{
	ID_KICK = 0,
	ID_INVITE = 1,
	ID_TOPIC = 2,
	ID_MODE = 3,
	ID_PING = 4
};

class Command
{
	private:
		std::string						_prefix; // @note potentially separate object / more complex, also the prefix doesn't belong to the command
		int								_id;
		std::vector<std::string>		_params;
	public:		
										Command();
										Command(std::string prefix, int id, std::vector<std::string> params);
										~Command();
		void							setPrefix(std::string prefix);
		void							setId(int id);
		void							addParam(std::string param);
		void							setParams(std::vector<std::string> params);
		const std::string&				getPrefix() const;
		const int&						getId() const;
		const std::vector<std::string>&	getParams() const;
};

#endif