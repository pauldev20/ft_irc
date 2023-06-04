#include "Command.hpp"

#include <string>

Command::Command(std::string prefix, int id, std::vector<std::string> params)
{
	this->prefix = prefix;
	this->id = id;
	this->_params = params;
}

Command::Command()
{
}

Command::~Command()
{
}

void	Command::setPrefix(std::string prefix)
{
	this->prefix = prefix;
}

void	Command::setId(int id)
{
	this->id = id;
}

void	Command::addParam(std::string param)
{
	this->_params.push_back(param);
}

void	Command::setParams(std::vector<std::string> params)
{
	this->_params = params;
}

const std::string&	Command::getPrefix() const
{
	return (this->prefix);
}

const int&	Command::getId() const
{
	return (this->id);
}

const std::vector<std::string>&	Command::getParams() const
{
	return (this->_params);
}