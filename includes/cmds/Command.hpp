/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:39:44 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/07 10:20:37 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Message.hpp"
#include "Server.hpp"
#include "Client.hpp"

class Message;

class Command {
	public:
		Command(bool needsPass = true, bool needsRegistration = true);
		~Command();

		void			execute(Message& message, Server* server, Client* client);

	private:
		bool		checkRegister;
		bool		checkPass;

	protected:
		virtual void	exec(Message& message, Server* server, Client* client) = 0;
		void			checkRegistered(Client *client) const;
};
