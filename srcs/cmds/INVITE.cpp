#include "cmds/Commands.hpp"

INVITE::INVITE(void) : Command() {
}

void INVITE::exec(Message& message, Server* server, Client* client) {
    // check the amount of params
    std::vector<std::string> params = message.getParams();
    if (params.size() < 2) {
        client->sendData(replies::ERR_NEEDMOREPARAMS("INVITE"));
        return ;
    }
    // check if the channel is valid
    Channel *channel = server->getChannelByName(params[1]);
    if (channel == NULL) {
        client->sendData(replies::ERR_NOSUCHCHANNEL(client->getNickname(), params[1]));
        return ;
    }
    // check if the user is valid
    Client *target = server->getClientByNickname(params[0]);
    if (target == NULL)
    {
        client->sendData(replies::ERR_NOSUCHNICK(client->getNickname(), params[1]));
        return ;
    }
    // check if the invited user is already in the channel
    if (channel->isClientInChannel(target))
    {
        client->sendData(replies::ERR_USERONCHANNEL(params[0], params[1]));
        return ;
    }
    // check if the channels mode (invite only or not)
    if (channel->isInviteOnly())
    {
        // if so, check if the client is an operator inside this channel
        if (channel->isOperator(client)) {
            // invite
        } else {
            client->sendData(replies::ERR_CHANOPRIVSNEEDED(client->getNickname(), params[1]));
            return ;
        }
    // if not, check if the client is inside the channel
    } else {
        if (!channel->isClientInChannel(client))
        {
            client->sendData(replies::ERR_NOTONCHANNEL(client->getNickname(), params[1]));
            return ;
        }
        // invite (only client and the user invited will receive the notification)
        // send notification to the user invited
        channel->addInvited(target);
        client->sendData(replies::RPL_INVITE(client->getNickname(), client->getUsername(), params[0], params[1]));
    }
}