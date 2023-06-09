#include "cmds/Commands.hpp"
#include "Channel.hpp"

TOPIC::TOPIC(void) : Command() {
}

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
    if (params.size() < 1 || message.getTrailing().empty()) {
        if (topic.empty()) {
            client->sendData(replies::RPL_NOTOPIC(client, params[0]));
            return ;
        } else {
            // @todo implement removal of topic
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
