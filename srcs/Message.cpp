/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 07:35:56 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/11 07:35:56 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"
#include "cmds/Command.hpp"

#include <string>

Message::Message() : _prefix(""), _cmd(NULL), _cmd_name(""), _params(0), _trailing(""), _has_trailing(false)
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

void	Message::setHasTrailing(bool has_trailing)
{
	this->_has_trailing = has_trailing;
}

std::string	Message::getPrefix() const
{
	return (this->_prefix);
}

Command*	Message::getCmd() const
{
	return (this->_cmd);
}

std::string	Message::getCmdName() const
{
	return (this->_cmd_name);
}

const std::vector<std::string>&	Message::getParams() const
{
	return (this->_params);
}

std::string	Message::getTrailing() const
{
	return (this->_trailing);
}

bool	Message::getHasTrailing() const
{
	return (this->_has_trailing);
}