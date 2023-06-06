/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:41:47 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/06 11:08:30 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Command.hpp"
#include "irc.hpp"

class Message;

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

class JOIN : public Command {
	public:
		JOIN(void);
		
	private:
		void exec(Message& message, Server* server, Client* client);
};

class PART : public Command {
	public:
		PART(void);
		
	private:
		void exec(Message& message, Server* server, Client* client);
};
