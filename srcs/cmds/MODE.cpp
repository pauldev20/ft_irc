
#include "cmds/Commands.hpp"
#include <sstream>

MODE::MODE(void) : Command () {
}

std::string MODE::getCurrentModes(Channel* channel) {
    std::string modeString;

    if (channel->isInviteOnly())
        modeString.append("i ");
    if (channel->isTopicRestriction())
        modeString.append("t ");
    if (channel->getPassword() != "")
        modeString.append("k ");
    if (channel->getUserLimit() != 0) {
        modeString.append("l=");
        std::ostringstream tmp;
        tmp << channel->getUserLimit();
        modeString.append(tmp.str());
    }
    return (modeString);
}

// @todo if the MODE cmd is called w/o arguments, the server should return the
// modes of the channel
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
    Channel *channel = server->getChannelByName(params[0]);
    // check if valid channel name was provided
    if (channel == NULL) {
        client->sendData(replies::ERR_NOSUCHCHANNEL(client, params[0]));
        return ;
    }
    if (params.size() < 2) {
        client->sendData(replies::RPL_CHANNELMODEIS(client, channel->getName(), getCurrentModes(channel)));
        return ;
    }
    // check if client is channel operator
    if (!channel->isOperator(client)) {
        client->sendData(replies::ERR_CHANOPRIVSNEEDED(client, channel->getName()));
        return ;
    }
    // also check if the provided flags can be executed
    // @note getParams[1], am I accessing the middle param this way?
    for (size_t i = 0; i < params[1].size(); i++) {
        if (flags.find(params[1].c_str(), i, 1) == std::string::npos
            && params[1].find("+") == std::string::npos
            && params[1].find("-") == std::string::npos) {
            client->sendData(replies::ERR_UMODEUNKNOWNFLAG(client));
            return ;
        } else {
            // if the flag is valid, exec the right function
            if (params[1][i] == 'i') {
                if (params[1][i - 1] == '+')
                    setInviteOnly(channel, true);
                else
                    setInviteOnly(channel, false);
            }
            if (params[1][i] == 't') {
                if (params[1][i - 1] == '+')
                    setTopicRestriction(channel, true);
                else
                    setTopicRestriction(channel, false);
            }
            if (params[1][i] == 'k') {
                if (params[1][i - 1] == '+') {
                    if (params.size() > 2)
                        setPassword(channel, params[2]);
                    else {
                        client->sendData(replies::ERR_NEEDMOREPARAMS(client, "MODE"));
                        return ;
                    }
                }
                else {
                    if (params.size() > 2) {
                        client->sendData(replies::ERR_TOOMANYARGS(client->getNickname(), params[1][i]));
                        return ;
                    } else {
                        setPassword(channel, "");
                    }
                }
            }
            if (params[1][i] == 'o') {
                if (params.size() < 3) {
                    client->sendData(replies::ERR_NEEDMOREPARAMS(client, "MODE"));
                    return ;
                }
                Client* target = server->getClientByNickname(params[2]);
                // @todo new operator dont get published into channel!!!!!!!!!
                if (target != NULL) {
                    if (params[1][i - 1] == '+')
                        setOperator(channel, target, true);
                    else
                        setOperator(channel, target, false);
                } else {
                    client->sendData(replies::ERR_NOSUCHNICK(client, params[2]));
                    return ;
                }
            }
            if (params[1][i] == 'l') {
                if (params[1][i - 1] == '+') {
                    if (params.size() > 2) {
                        std::stringstream sstream(params[2]);
                        size_t limit;
                        sstream >> limit;
                        setUserLimit(channel, limit);
                    }
                    else {
                        client->sendData(replies::ERR_NEEDMOREPARAMS(client, "MODE"));
                        return ;
                    }
                }
                else {
                    if (params.size() > 2) {
                        client->sendData(replies::ERR_TOOMANYARGS(client->getNickname(), params[1][i]));
                        return ;
                    } else {
                        setUserLimit(channel, 0);
                    }
                }
            }
            if (params[1][i] != '+' && params[1][i] != '-') {
                modeString.push_back(params[1].c_str()[i - 1]);
                modeString.push_back(params[1].c_str()[i]);
            }
        }
    }
    // this is send at the very end
    // @note check if the user changing the mode is receiving some kind of msg
    channel->sendMessageToAll(replies::RPL_SETMODECHANNEL(client, channel->getName(), modeString));
}

// i - set/remove invite-only; operator only
// will be called if the i flag is encountered
// if the set bool is false, the flag is removed
void MODE::setInviteOnly(Channel* channel, bool set) {
    channel->setInviteOnly(set);
}

void MODE::setTopicRestriction(Channel* channel, bool set) {
    channel->setTopicRestriction(set);
}

// @note in order to be able to call it, a third parameter needs to be defined
// the user whose priviliges needs to be changed
void MODE::setOperator(Channel* channel, Client* target, bool set) {
    if (set)
        channel->addOperator(target);
    else
        channel->removeOperator(target);
}

// @note inside exec, we need to check whether a password is provided
// if not, then password is an empty string
// if the user calls +k without a password, an error should be returned
void MODE::setPassword(Channel* channel, std::string password) {
    channel->setPassword(password);
}

// @note inside exec, we need to check whether a limit is provided
// if not, then limit is 0
// if the user calls +l without a limit, an error should be returned
void MODE::setUserLimit(Channel *channel, size_t limit) {
    channel->setUserLimit(limit);
}
