
#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Server.hpp"
#include "Client.hpp"
#include "cmds/Command.hpp"

#include <string>
#include <vector>

class Command;
// @todo circular dependency fuck shit

class Message
{
	private:
		std::string						_prefix; // @note potentially separate object / more complex, also the prefix doesn't belong to the command
		Command*						_cmd;
		std::string						_cmd_name;
		std::vector<std::string>		_params;
	public:		
										Message();
										Message(std::string prefix, Command* cmd, std::string cmd_name, std::vector<std::string> params);
										~Message();
		void							setPrefix(std::string prefix);
		void							setCmd(Command* cmd);
		void							setCmdName(std::string cmd_name);
		void							setCmdAll(Command* cmd, std::string cmd_name);
		void							addParam(std::string param);
		void							setParams(std::vector<std::string> params);
		const std::string&				getPrefix() const;
		Command*						getCmd() const;
		const std::string				getCmdName() const;
		const std::vector<std::string>&	getParams() const;
};

#endif