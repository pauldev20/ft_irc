/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:41:47 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/06 01:39:27 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Command.hpp"
#include "irc.hpp"

class CAP : public Command {
	public:
		CAP(void);
	
	private:
		void exec(Message& message, Server* server, Client* client);
};

class PING : public Command {
	public:
		PING(void);
		
	private:
		void exec(Message& message, Server* server, Client* client);
};

class PASS : public Command {
	public:
		PASS(void);
		
	private:
		void exec(Message& message, Server* server, Client* client);
};

class NICK : public Command {
	public:
		NICK(void);
		
	private:
		void exec(Message& message, Server* server, Client* client);
};

class USER : public Command {
	public:
		USER(void);
		
	private:
		void exec(Message& message, Server* server, Client* client);
};

class QUIT : public Command {
	public:
		QUIT(void);
		
	private:
		void exec(Message& message, Server* server, Client* client);
};

class PRIVMSG : public Command {
	public:
		PRIVMSG(void);
		
	private:
		void exec(Message& message, Server* server, Client* client);
};
