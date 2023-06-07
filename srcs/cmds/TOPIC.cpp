#include "cmds/Commands.hpp"
#include "Channel.hpp"

// @note correct with true, true?
TOPIC::TOPIC(void) : Command(true, true) {
}

void TOPIC::exec(Message& message, Server* server, Client* client) {
    std::vector<std::string> params = message.getParams();
    if (server->getChannelByName(params[0]) == NULL) {
        client->sendData(replies::ERR_NOSUCHCHANNEL(client->getNickname(), params[0]));
        return ;
    }
    Channel *channel = server->getChannelByName(params[0]);
    std::string topic = server->getChannelByName(params[0])->getTopic();
    // need to check if the client is part of the channel
    // @note if param == 1, the topic of the channel needs to be returned
    if (params.size() == 1) {
        if (topic.empty()) {
            client->sendData(replies::RPL_NOTOPIC(client->getNickname(), params[0]));
            return ;
        } else {
            client->sendData(replies::RPL_TOPIC(client->getNickname(), params[0], topic));
            return ;
        }
    }
    if (params.size() == 2) {
        // @note if user is not operator, he cannot change the topic
        if (!channel->isOperator(client)) {
            client->sendData(replies::ERR_CHANOPRIVSNEEDED(client->getNickname(), params[0]));
            return ;
        }
        // topic needs to be set. but if the second param is empty, the topic needs to be removed
        if (params[1].empty()) {
            channel->setTopic("");
            // @note is this correct?
            channel->sendMessageToAllExcept(":" + client->getNickname() + " TOPIC " + params[0] + " :" + params[1] + "\r\n", client);
            return ;
        } else {
            channel->setTopic(params[1]);
            // @note is this correct?
            channel->sendMessageToAllExcept(":" + client->getNickname() + " TOPIC " + params[0] + " :" + params[1] + "\r\n", client);
            return ;
        }
    }
}