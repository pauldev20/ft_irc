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

class KICK : public Command {
    public:
        KICK(void);

    private:
        void exec(Message& message, Server* server, Client* client);
};

class TOPIC : public Command {
    public:
        TOPIC(void);

    private:
        void exec(Message& message, Server* server, Client* client);
};

class INVITE : public Command {
    public:
        INVITE(void);

    private:
        void exec(Message& message, Server* server, Client* client);
};

class MODE : public Command {
    public:
        MODE(void);

    private:
        void exec(Message& message, Server* server, Client* client);
        void setInviteOnly(Channel* channel, bool set);
        void setTopicRestriction(Channel* channel, bool set);
        void setOperator(Channel* channel, Client* target, bool set);
        void setPassword(Channel* channel, std::string password);
        void setUserLimit(Channel *channel, size_t limit);
};
