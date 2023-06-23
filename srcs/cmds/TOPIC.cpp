/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 07:35:30 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/23 18:59:19 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"
#include "Channel.hpp"

TOPIC::TOPIC(void) : Command() {
}

/**
 * This function allows a client to set or retrieve the topic of a
 * channel in an IRC server.
 * 
 * @param message The message object that contains the command and its
 * parameters sent by the client.
 * @param server A pointer to the Server object that the TOPIC
 * command is being executed on.
 * @param client The "client" parameter is a pointer to the
 * client who sent the message that triggered the execution of this function.
 * 
 * @return nothing (void).
 */
void TOPIC::exec(Message& message, Server* server, Client* client) {
    std::vector<std::string> params = message.getParams();
    Channel *channel = server->getChannelByName(params[0]);
    if (!channel) {
        client->sendData(replies::ERR_NOSUCHCHANNEL(client, params[0]));
        return ;
    }
    std::string topic = server->getChannelByName(params[0])->getTopic();
    if (!channel->isClientInChannel(client)) {
        client->sendData(replies::ERR_NOTONCHANNEL(client, params[0]));
        return ;
    }
    if (params.size() < 1 || !message.getHasTrailing()) {
        if (topic.empty()) {
            client->sendData(replies::RPL_NOTOPIC(client, params[0]));
            return ;
        } else {
            client->sendData(replies::RPL_TOPIC(client, params[0], topic));
            return ;
        }
    }
    if (channel->isTopicRestriction() && !channel->isOperator(client)) {
        client->sendData(replies::ERR_CHANOPRIVSNEEDED(client, params[0]));
        return ;
    }
    channel->setTopic(message.getTrailing());
    channel->sendMessageToAll(replies::RPL_TOPICCHANGE(client, params[0], message.getTrailing()));
}
