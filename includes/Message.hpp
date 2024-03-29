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

#define PARAM_MAX 15

class Command;

class Message
{
	private:
		std::string						_prefix;
		Command*						_cmd;
		std::string						_cmd_name;
		std::vector<std::string>		_params;
		std::string						_trailing;
		bool							_has_trailing;
	public:
										Message();
										~Message();
		void							setPrefix(std::string prefix);
		void							setCmd(Command* cmd);
		void							setCmdName(std::string cmd_name);
		void							setCmdAll(Command* cmd, std::string cmd_name);
		void							addParam(std::string param);
		void							setParams(std::vector<std::string> params);
		void							setTrailing(std::string trailing);
		void							setHasTrailing(bool is_trailing_empty);
		std::string						getPrefix() const;
		Command*						getCmd() const;
		std::string						getCmdName() const;
		const std::vector<std::string>&	getParams() const;
		std::string						getTrailing() const;
		bool							getHasTrailing() const;
};
