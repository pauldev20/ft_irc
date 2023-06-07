
#include "cmds/Commands.hpp"
#include <sstream>

// @note correct with false, false?
MODE::MODE(void) : Command (false, false) {
}

// @note if one instruction should fail bc of false parameters or similar stuff,
// the whole command should fail, providing the client with the error that caused
// the termiation. This should be handled by the exec command
void MODE::exec(Message& message, Server* server, Client* client) {
    // @note after every mode change, it is appended to the modeString
    // alternatively, the modeString can be passed to the funtions, and the
    // correct change can be appended there
    std::string modeString;
    std::string flags = "itkol";
    std::vector<std::string> params = message.getParams();
    // flags can be called like '+i-t' or '+i,-t'
    // need to check if there are at least 2 params (channel name and flags as one string)
    if (params.size() < 2) {
        client->addDataToBuffer(replies::ERR_NEEDMOREPARAMS("MODE"));
        client->sendData();
        return ;
    }
    Channel *channel = server->getChannelByName(params[0]);
    // check if valid channel name was provided
    if (channel == NULL) {
        client->addDataToBuffer(replies::ERR_NOSUCHCHANNEL(client->getNickname(), params[0]));
        client->sendData();
        return ;
    }
    // check if client is channel operator
    if (!channel->isOperator(client)) {
        client->addDataToBuffer(replies::ERR_CHANOPRIVSNEEDED(client->getNickname(), channel->getName()));
        client->sendData();
        return ;
    }
    // also check if the provided flags can be executed
    // @note getParams[1], am I accessing the middle param this way?
    for (size_t i = 0; i < params[1].size(); i++) {
        if (flags.find(params[1][i]) == std::string::npos
            && flags.find("+") == std::string::npos
            && flags.find("-") == std::string::npos) {
            client->addDataToBuffer(replies::ERR_UNKNOWNMODE(client->getNickname(), params[1][i]));
            client->sendData();
            return ;
        } else {
            // if the flag is valid, exec the right function
            if (params[1][i] == (const char)"i") {
                if (params[1][i - 1] == (const char)"+")
                    setInviteOnly(channel, client, true);
                else
                    setInviteOnly(channel, client, false);
                modeString += params[1][i - 1] + params[1][i];
            }
            if (params[1][i] == (const char)"t") {
                if (params[1][i - 1] == (const char)"+")
                    setTopicRestriction(channel, client, true);
                else
                    setTopicRestriction(channel, client, false);
            }
            if (params[1][i] == (const char)"k") {
                if (params[1][i - 1] == (const char)"+") {
                    if (params.size() > 2)
                        setPassword(channel, client, params[2]);
                    else {
                        client->addDataToBuffer(replies::ERR_NEEDMOREPARAMS("MODE"));
                        client->sendData();
                        return ;
                    }
                }
                else {
                    if (params.size() > 2) {
                        client->addDataToBuffer(replies::ERR_TOOMANYARGS(client->getNickname(), params[1][i]));
                        client->sendData();
                        return ;
                    } else {
                        setPassword(channel, client, "");
                    }
                }
            }
            if (params[1][i] == (const char)"o") {
                if (params.size() < 3) {
                    client->addDataToBuffer(replies::ERR_NEEDMOREPARAMS("MODE"));
                    client->sendData();
                    return ;
                }
                Client* target = server->getClientByNickname(params[2]);
                if (target != NULL) {
                    if (params[1][i - 1] == (const char)"+")
                        setOperator(channel, client, target, true);
                    else
                        setOperator(channel, client, target, false);
                } else {
                    client->addDataToBuffer(replies::ERR_NOSUCHNICK(client->getNickname(), params[2]));
                    client->sendData();
                    return ;
                }
            }
            if (params[1][i] == (const char)"l") {
                if (params[1][i - 1] == (const char)"+") {
                    if (params.size() > 2) {
                        std::stringstream sstream(params[2]);
                        size_t limit;
                        sstream >> limit;
                        setUserLimit(channel, client, limit);
                    }
                    else {
                        client->addDataToBuffer(replies::ERR_NEEDMOREPARAMS("MODE"));
                        client->sendData();
                        return ;
                    }
                }
                else {
                    if (params.size() > 2) {
                        client->addDataToBuffer(replies::ERR_TOOMANYARGS(client->getNickname(), params[1][i]));
                        client->sendData();
                        return ;
                    } else {
                        setUserLimit(channel, client, 0);
                    }
                }
            }
        }
    }
    // this is send at the very end
    // @note check if the user changing the mode is receiving some kind of msg
    client->addDataToBuffer(replies::RPL_CHANNELMODEIS(client->getNickname(), client->getUsername(), channel->getName(), modeString));
    client->sendData();
}

// i - set/remove invite-only; operator only
// will be called if the i flag is encountered
// if the set bool is false, the flag is removed
void MODE::setInviteOnly(Channel* channel, Client* client, bool set) {
    channel->setInviteOnly(set);
}

void MODE::setTopicRestriction(Channel* channel, Client* client, bool set) {
    channel->setTopicRestriction(set);
}

// @note in order to be able to call it, a third parameter needs to be defined
// the user whose priviliges needs to be changed
void MODE::setOperator(Channel* channel, Client* client, Client* target, bool set) {
    if (set)
        channel->addOperator(target);
    else
        channel->removeOperator(target);
}

// @note inside exec, we need to check whether a password is provided
// if not, then password is an empty string
// if the user calls +k without a password, an error should be returned
void MODE::setPassword(Channel* channel, Client* client, std::string password) {
    channel->setPassword(password);
}

// @note inside exec, we need to check whether a limit is provided
// if not, then limit is 0
// if the user calls +l without a limit, an error should be returned
void MODE::setUserLimit(Channel *channel, Client* client, size_t limit) {
    channel->setUserLimit(limit);
}
