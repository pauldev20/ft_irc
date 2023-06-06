#include "Message.hpp"

#include <string>

Message::Message(std::string prefix, int id, std::vector<std::string> params)
{
	this->_prefix = prefix;
	this->_id = id;
	this->_params = params;
}

Message::Message()
{
}

Message::~Message()
{
}

void	Message::setPrefix(std::string prefix)
{
	this->_prefix = prefix;
}

void	Message::setId(int id)
{
	this->_id = id;
}

void	Message::addParam(std::string param)
{
	this->_params.push_back(param);
}

void	Message::setParams(std::vector<std::string> params)
{
	this->_params = params;
}

const std::string&	Message::getPrefix() const
{
	return (this->_prefix);
}

const int&	Message::getId() const
{
	return (this->_id);
}

const std::vector<std::string>&	Message::getParams() const
{
	return (this->_params);
}