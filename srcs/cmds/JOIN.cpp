/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:11:40 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/09 22:51:45 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"
#include "Channel.hpp"
#include <sstream>	    // std::stringstream
#include <vector>       // std::vector
#include <algorithm>	// std::find

/**
 * The function checks if a given string is a valid channel name by verifying if it starts with a '#'
 * character.
 * 
 * @param name The parameter "name" is a constant reference to a string, which is the name of a channel
 * being checked for validity.
 * 
 * @return A boolean value is being returned.
 */
static bool	checkChannelNameValidity(std::string const &name) {
	if (name.size() > 0 && name[0] != '#') {
		return false;
	}
	return true;
}

JOIN::JOIN(void) : Command() {
}

/**
 * The JOIN function allows a client to join one or more channels on a server, creating a new channel
 * if it does not exist, and sending appropriate error messages if necessary.
 * 
 * @param message The message object contains information about the JOIN command that was received,
 * including the parameters passed with it (such as the name of the channel to join and any password
 * provided).
 * @param server The server object represents the IRC server and contains information about all the
 * channels and clients connected to it.
 * @param client The client who sent the JOIN command.
 */
void JOIN::exec(Message& message, Server* server, Client* client) {
    std::vector<std::string> channel_list = this->splitString(message.getParams()[0], ',');
    for (size_t i = 0; i < channel_list.size(); i++) {
		if (checkChannelNameValidity(channel_list[i]) == false) {
			client->sendData(replies::ERR_NOSUCHCHANNEL(client, message.getParams()[0]));
			continue ;
		}
        Channel *channel = server->getChannelByName(channel_list[i]);
        if (channel == NULL) {
            channel = new Channel(client, channel_list[i], message.getParams().size() > 1 ? message.getParams()[1] : "");
            server->addChannel(channel);
        } else {
            try {
				if (channel->getPassword() != "") {
					if (message.getParams().size() < 2 || message.getParams()[1] != channel->getPassword()) {
						client->sendData(replies::ERR_CHANOPRIVSNEEDED(client, channel->getName()));
						continue ;
					}
				}
				channel->addClient(client);
            } catch (const Channel::ChannelFullExcpetion &e) {
                client->sendData(replies::ERR_CHANNELISFULL(client, channel->getName()));
                continue ;
            } catch (const Channel::InviteOnlyExcpetion &e) {
                client->sendData(replies::ERR_INVITEONLYCHAN(client, channel->getName()));
                continue ;
            } catch (const Channel::AllreadyInChannelExcpetion &e) {
                client->sendData(replies::ERR_CHANNELISFULL(client, channel->getName()));
                continue ;
            }
        }
		channel->sendMessageToAll(replies::RPL_JOIN(client, channel->getName()));
        std::vector<Client*> clients = channel->getClients();
        std::vector<Client*> operators = channel->getOperators();
        std::string clientList = "";
        for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); it++) {
            if (std::find(operators.begin(), operators.end(), *it) != operators.end())
                clientList += "@" + (*it)->getNickname() + " ";
            else
                clientList += (*it)->getNickname() + " ";
            if (clientList.size() > 400) {
                client->sendData(replies::RPL_NAMREPLY(client, channel->getName(), clientList));
                clientList = "";
            }
        }
		client->sendData(replies::RPL_NAMREPLY(client, channel->getName(), clientList));
		client->sendData(replies::RPL_ENDOFNAMES(client, channel->getName()));
    }
}
