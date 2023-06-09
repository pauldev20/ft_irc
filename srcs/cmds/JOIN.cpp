/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:11:40 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/09 22:38:23 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"
#include "Channel.hpp"
#include <sstream>	    // std::stringstream
#include <vector>       // std::vector
#include <algorithm>	// std::find

static bool	checkChannelNameValidity(std::string const &name) {
	if (name.size() > 0 && name[0] != '#') {
		return false;
	}
	return true;
}

JOIN::JOIN(void) : Command() {
}

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
