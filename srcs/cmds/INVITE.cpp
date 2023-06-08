#include "cmds/Commands.hpp"

INVITE::INVITE(void) : Command() {
}

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
