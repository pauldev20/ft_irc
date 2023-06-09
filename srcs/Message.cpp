
#include "Message.hpp"
#include "cmds/Command.hpp"

#include <string>

Message::Message() : _prefix(""), _cmd(NULL), _cmd_name(""), _params(0), _trailing("")
{
}

Message::~Message()
{
}

void	Message::setPrefix(std::string prefix)
{
	this->_prefix = prefix;
}

void	Message::setCmd(Command* cmd)
{
	this->_cmd = cmd;
}

void	Message::setCmdName(std::string cmd_name)
{
	this->_cmd_name = cmd_name;
}

void	Message::setCmdAll(Command* cmd, std::string cmd_name)
{
	this->_cmd = cmd;
	this->_cmd_name = cmd_name;
}

void	Message::addParam(std::string param)
{
	if (!param.empty())
		this->_params.push_back(param);
}

void	Message::setParams(std::vector<std::string> params)
{
	this->_params = params;
}

void	Message::setTrailing(std::string trailing)
{
	this->_trailing = trailing;
}

const std::string&	Message::getPrefix() const
{
	return (this->_prefix);
}

Command*	Message::getCmd() const
{
	return (this->_cmd);
}

const std::string	Message::getCmdName() const
{
	return (this->_cmd_name);
}

const std::vector<std::string>&	Message::getParams() const
{
	return (this->_params);
}

const std::string&	Message::getTrailing() const
{
	return (this->_trailing);
}