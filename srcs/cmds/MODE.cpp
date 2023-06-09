
#include "cmds/Commands.hpp"
#include <sstream>

#define MODE_FLAGS "itokl"

MODE::MODE(void) : Command()
{
}


bool isNumber(const std::string& str) {
    std::istringstream iss(str);
    int number;
    return (iss >> number >> std::ws) && iss.eof();
}

std::string MODE::getCurrentModes(Channel *channel)
{
    std::string modeString;

    if (channel->isInviteOnly())
        modeString.append("i ");
    if (channel->isTopicRestriction())
        modeString.append("t ");
    if (channel->getPassword() != "")
        modeString.append("k ");
    if (channel->getUserLimit() != 0)
    {
        modeString.append("l=");
        std::ostringstream tmp;
        tmp << channel->getUserLimit();
        modeString.append(tmp.str());
    }
    return (modeString);
}

bool    MODE::isValidCall(std::vector<std::string> params, Channel* channel, Client* client, std::string flags)
{
    if (channel == NULL)
    {
        client->sendData(replies::ERR_NOSUCHCHANNEL(client, params[0]));
        return (false);
    }
    if (params.size() < 2)
    {
        client->sendData(replies::RPL_CHANNELMODEIS(client, channel->getName(), getCurrentModes(channel)));
        return (false);
    }
    if (!channel->isOperator(client))
    {
        client->sendData(replies::ERR_CHANOPRIVSNEEDED(client, channel->getName()));
        return (false);
    }
    for (size_t i = 0; i < params[1].size(); i++)
    {
        if (flags.find_first_of(params[1].c_str()) == std::string::npos && params[1][i] != '+' && params[1][i] != '-')
        {
            client->sendData(replies::ERR_UMODEUNKNOWNFLAG(client));
            return (false);
        }
    }
    return (true);
}


// @todo need to throw error when the pwd has incorrect format?
void MODE::exec(Message &message, Server *server, Client *client)
{
    bool addOrRemove = true;
    bool success = false;
    std::string modeString = "";
    std::string flags = MODE_FLAGS;
    std::vector<std::string> params = message.getParams();
    Channel* channel = server->getChannelByName(params[0]);
    if (!isValidCall(params, channel, client, flags))
        return;
    for (size_t i = 0; i < params[1].size(); i++)
    {
        if (params[1][i] == '+' || params[1][i] == '-')
        {
            if (params[1][i] == '-')
                addOrRemove = false;
            else
                addOrRemove = true;
            modeString.push_back(params[1][i]);
            i++;
            while (isalpha(params[1][i]))
            {
                if (params[1][i] == 'i')
                    success = setInviteOnly(channel, addOrRemove);
                else if (params[1][i] == 't')
                    success = setTopicRestriction(channel, addOrRemove);
                else if (params[1][i] == 'k')
                    success = setPassword(channel, params, client, addOrRemove);
                else if (params[1][i] == 'o')
                    success = setOperator(channel, client, server, params, addOrRemove);
                else if (params[1][i] == 'l')
                    success = setUserLimit(channel, client, params, addOrRemove);
                if (success)
                {
                    modeString.push_back(params[1][i]);
                    success = false;
                }
                if (params[1][i + 1] != '+' && params[1][i + 1] != '-')
                    i++;
                else
                    break;
            }
        }
        if (i == 0 && params[1][i] != '+' && params[1][i] != '-')
        {
            client->sendData(replies::ERR_UMODEUNKNOWNFLAG(client));
            return;
        }
    }
    channel->sendMessageToAllExcept(replies::RPL_SETMODECHANNEL(client, channel->getName(), modeString), client);
    channel->sendMessageToAll(replies::RPL_SETMODECLIENT(client, channel->getName(), modeString, params[2]));
}

bool MODE::setInviteOnly(Channel *channel, bool set)
{
    channel->setInviteOnly(set);
    return (true);
}

bool MODE::setTopicRestriction(Channel *channel, bool set)
{
    channel->setTopicRestriction(set);
    return (true);
}

bool MODE::setOperator(Channel *channel, Client *client, Server* server, std::vector<std::string> params, bool set)
{
    Client* target = server->getClientByNickname(params[2]);
    if (target != NULL)
    {
        if (set)
            channel->addOperator(target);
        else
            channel->removeOperator(target);
    }
    else
    {
        client->sendData(replies::ERR_NOSUCHNICK(client, params[2]));
        return (false);
    }
    return (true);
}

bool MODE::setPassword(Channel *channel, std::vector<std::string> params, Client *client, bool addOrRemove)
{
    if (addOrRemove && params.size() > 2)
        channel->setPassword(params[2]);
    else if (!addOrRemove)
        channel->setPassword("");
    else
    {
        client->sendData(replies::ERR_NEEDMOREPARAMS(client, "MODE"));
        return (false);
    }
    return (true);
}

bool MODE::setUserLimit(Channel *channel, Client *client, std::vector<std::string> params, bool addOrRemove)
{
    if (addOrRemove && params.size() > 2)
    {
        if (isNumber(params[2]))
        {
            std::stringstream sstream(params[2]);
            size_t limit;
            sstream >> limit;
            channel->setUserLimit(limit);
        }
        else
        {
            // send msg regarding wrong argument
            return (false);
        }
    }
    else if (!addOrRemove)
        channel->setUserLimit(0);
    else
    {
        client->sendData(replies::ERR_NEEDMOREPARAMS(client, "MODE"));
        return (false);
    }
    return (true);
}
