
#include "cmds/Commands.hpp"

KICK::KICK(void) : Command(true, true) {
}

void KICK::exec(Message& message, Server* server, Client* client) {
    std::vector<std::string> params = message.getParams();
    if (params.size() < 2) {
        client->sendData(replies::ERR_NEEDMOREPARAMS("KICK"));
        return ;
    }
    Channel *channel = server->getChannelByName(params[0]);
    if (channel->checkChannelNameValidity(params[0]) == false) {
        client->sendData(replies::ERR_NOSUCHCHANNEL(client->getNickname(), params[0]));
        return ;
    }
    if (channel == NULL) {
        client->sendData(replies::ERR_NOSUCHCHANNEL(client->getNickname(), params[0]));
        return ;
    }
    if (!channel->isClientInChannel(client)) {
        client->sendData(replies::ERR_NOTONCHANNEL(client->getNickname(), params[0]));
        return ;
    }
    Client *target = server->getClientByNickname(params[1]);
    if (target == NULL) {
        client->sendData(replies::ERR_NOSUCHNICK(client->getNickname(), params[0]));
        return ;
    }
    if (!channel->isClientInChannel(target)) {
        client->sendData(replies::ERR_USERNOTINCHANNEL(params[1], params[0]));
        return ;
    }
    channel->removeClient(target);
}