/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 22:51:26 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/23 18:44:23 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"

INVITE::INVITE(void) : Command() {
}

/**
 * This function handles the INVITE command in an IRC server, inviting a client
 * to a channel if they meet certain conditions.
 * 
 * @param message A reference to a Message object, which contains information
 * about the incoming message from the client.
 * @param server A pointer to the Server object that the INVITE command is
 * being executed on.
 * @param client The client who sent the INVITE command.
 * 
 * @return The function does not return anything, it uses the `return` keyword
 * to exit the function early in case of certain conditions being met.
 */
void INVITE::exec(Message& message, Server* server, Client* client) {
    std::vector<std::string> params = message.getParams();
    if (params.size() < 2) {
        client->sendData(replies::ERR_NEEDMOREPARAMS(client, "INVITE"));
        return ;
    }
    Channel *channel = server->getChannelByName(params[1]);
    if (channel == NULL) {
        client->sendData(replies::ERR_NOSUCHCHANNEL(client, params[1]));
        return ;
    }
    Client *target = server->getClientByNickname(params[0]);
    if (target == NULL)
    {
        client->sendData(replies::ERR_NOSUCHNICK(client, params[1]));
        return ;
    }
    if (target->isRegistered() == false)
    {
        client->sendData(replies::ERR_NOSUCHNICK(client, params[1]));
        return ;
    }
    if (channel->isClientInChannel(target))
    {
        client->sendData(replies::ERR_USERONCHANNEL(client, target, params[1]));
        return ;
    }
    if (channel->isInviteOnly())
    {
        if (channel->isOperator(client)) {
            client->sendData(replies::RPL_INVITE(client, params[1], params[0]));
            target->sendData(replies::RPL_INVITE(client, params[1], params[0]));
            channel->addInvited(target);
        } else {
            client->sendData(replies::ERR_CHANOPRIVSNEEDED(client, params[1]));
            return ;
        }
    } else {
        client->sendData(replies::RPL_INVITE(client, params[1], params[0]));
        target->sendData(replies::RPL_INVITE(client, params[1], params[0]));
        channel->addInvited(target);
    }
}
