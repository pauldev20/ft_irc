
#include "cmds/Commands.hpp"

// @note correct with false, false?
KICK::KICK(void) : Command (false, false) {
}

void KICK::exec(Message& message, Server* server, Client* client) {
    std::vector<std::string> params = message.getParams();
    if (params.size() < 2) {
        client->addDataToBuffer(replies::ERR_NEEDMOREPARAMS("KICK"));
        client->sendData();
        return ;
    }
    Channel *channel = server->getChannelByName(params[0]);
    if (channel->checkChannelNameValidity(params[0]) == false) {
        client->addDataToBuffer(replies::ERR_NOSUCHCHANNEL(client->getNickname(), params[0]));
        client->sendData();
        return ;
    }
    if (channel == NULL) {
        client->addDataToBuffer(replies::ERR_NOSUCHCHANNEL(client->getNickname(), params[0]));
        client->sendData();
        return ;
    }
    if (!channel->isClientInChannel(client))
    {
        client->addDataToBuffer(replies::ERR_NOTONCHANNEL(client->getNickname(), params[0]));
        client->sendData();
        return ;
    }
    Client *target = server->getClientByNickname(params[1]);
    if (target == NULL)
    {
        client->addDataToBuffer(replies::ERR_NOSUCHNICK(client->getNickname(), params[0]));
        client->sendData();
        return ;
    }
    if (!channel->isClientInChannel(target))
    {
        client->addDataToBuffer(replies::ERR_USERNOTINCHANNEL(params[1], params[0]));
        client->sendData();
        return ;
    }
    channel->removeClient(target);
}