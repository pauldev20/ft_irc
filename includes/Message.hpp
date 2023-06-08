/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:05:04 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/08 10:05:29 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
#include "Client.hpp"

#include <string>
#include <vector>

class Command;

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
