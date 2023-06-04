#pragma once

#include <vector>		// std::vector
#include "Client.hpp"	// CanClient

/* -------------------------------------------------------------------------- */
/*                                   Classes                                  */
/* -------------------------------------------------------------------------- */

class Channel {
	public:
		Channel(Client *admin, std::string const &channelName);
		~Channel(void);

		std::string const &getName(void) const;
		void	setName(std::string const &name);

		Client	*getAdmin(void) const;
	
		void	addClient(Client *client);
		void	removeClient(Client *client);

		void	kickClient(Client *client);
		void	unKickClient(Client *client);

		void	sendMessageToAll(std::string const &message);
		void	sendMessageToAllExcept(std::string const &message, Client *client);

		class AllreadyInChannelExcpetion: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class KickedClientExcpetion: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

	private:
		std::string				name;
		std::vector<Client*>	clients;
		std::vector<Client*>	kicked;
};
