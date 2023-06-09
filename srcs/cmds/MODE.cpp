/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 22:52:52 by pgeeser           #+#    #+#             */
/*   Updated: 2023/06/09 22:52:54 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds/Commands.hpp"
#include <sstream>

#define MODE_FLAGS "itokl"

MODE::MODE(void) : Command()
{
}

/**
 * The function returns a string containing the current modes of a given channel.
 * 
 * @param channel A pointer to a Channel object, which contains information about a chat channel in a
 * messaging application.
 * 
 * @return A string containing the current modes of the given channel, represented by a combination of
 * letters and symbols. The letters "i", "t", and "k" indicate whether the channel is invite-only, has
 * topic restriction, or has a password set, respectively. The letter "l" followed by an equal sign and
 * a number indicates the user limit of the channel.
 */
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

/**
 * This function checks if a given call is valid for a channel and client in an IRC server.
 * 
 * @param params A vector of strings containing the parameters passed to the function.
 * @param channel A pointer to a Channel object representing the channel the client is currently in.
 * @param client A pointer to the client who is attempting to make the call.
 * @param flags The "flags" parameter is a string that represents the mode flags that are being set or
 * unset in a channel. It is used to check if the flags are valid and can be applied to the channel.
 * 
 * @return The function `isValidCall` returns a boolean value (`true` or `false`) depending on whether
 * the call to change the channel mode is valid or not.
 */
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

/**
 * This function handles the execution of the MODE command in an IRC server, allowing clients to modify
 * channel modes.
 * 
 * @param message The message object that contains the MODE command and its parameters sent by the
 * client.
 * @param server A pointer to the Server object that the MODE command is being executed on.
 * @param client The client who sent the MODE command.
 * 
 * @return The function does not return anything, it has a void return type.
 */
void MODE::exec(Message &message, Server *server, Client *client)
{
    bool addOrRemove = true;
    bool success = false;
    std::string modeString = "";
    std::string targetString = "";
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
            targetString = params.size() > 2 ? params[2] : "";
            while (isalpha(params[1][i]))
            {
                if (params[1][i] == 'i')
                    success = setInviteOnly(channel, addOrRemove);
                else if (params[1][i] == 't')
                    success = setTopicRestriction(channel, addOrRemove);
                else if (params[1][i] == 'k') {
                    success = setPassword(channel, params, client, addOrRemove);
                    if (success)
                        targetString = "";
                }
                else if (params[1][i] == 'o')
                    success = setOperator(channel, client, server, params, addOrRemove);
                else if (params[1][i] == 'l')
                    success = setUserLimit(channel, client, params, addOrRemove);
                if (success)
                    modeString.push_back(params[1][i]);
                else
                    break;
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
    if (success)
        channel->sendMessageToAll(replies::RPL_SETMODECLIENT(client, channel->getName(), modeString, targetString));
}

/**
 * This function sets the invite-only mode of a channel in C++.
 * 
 * @param channel a pointer to a Channel object, which represents a chat room or a group in a messaging
 * application.
 * @param set A boolean value indicating whether the channel should be set to invite-only or not. If
 * set to true, the channel will only allow users who have been invited by a channel operator to join.
 * If set to false, the channel will allow anyone to join without an invitation.
 * 
 * @return a boolean value of `true`.
 */
bool MODE::setInviteOnly(Channel *channel, bool set)
{
    channel->setInviteOnly(set);
    return (true);
}

/**
 * This function sets the topic restriction of a channel in a C++ program.
 * 
 * @param channel A pointer to an object of the class Channel. This object represents a chat channel in
 * a messaging application.
 * @param set A boolean value indicating whether to set the topic restriction or not. If set to true,
 * the topic restriction will be enabled for the given channel. If set to false, the topic restriction
 * will be disabled.
 * 
 * @return a boolean value of `true`.
 */
bool MODE::setTopicRestriction(Channel *channel, bool set)
{
    channel->setTopicRestriction(set);
    return (true);
}

/**
 * This function sets or removes operator status for a client in a channel.
 * 
 * @param channel A pointer to the Channel object that the MODE command is being applied to.
 * @param client A pointer to the client who sent the MODE command.
 * @param server A pointer to the Server object.
 * @param params A vector of strings containing the parameters passed to the MODE command.
 * @param set A boolean value indicating whether the mode is being set or unset. If it is true, the
 * mode is being set. If it is false, the mode is being unset.
 * 
 * @return a boolean value.
 */
bool MODE::setOperator(Channel *channel, Client *client, Server* server, std::vector<std::string> params, bool set)
{
    if (params.size() < 3)
    {
        client->sendData(replies::ERR_NEEDMOREPARAMS(client, "MODE"));
        return (false);
    }   
    Client* target = server->getClientByNickname(params[2]);
    if (target != NULL)
    {
        if (set && channel->isClientInChannel(target))
        {
            channel->addOperator(target);
            return (true);
        }
        else if (!set && channel->isClientInChannel(target))
        {
            channel->removeOperator(target);
            return (true);
        }
        client->sendData(replies::ERR_NOSUCHNICK(client, params[2]));
        return (false);
    }
    else
    {
        client->sendData(replies::ERR_NOSUCHNICK(client, params[2]));
        return (false);
    }
}

/**
 * This function sets a password for a channel or removes it based on the parameters passed to it.
 * 
 * @param channel A pointer to the Channel object that the password is being set for.
 * @param params A vector of strings containing the parameters passed to the function.
 * @param client A pointer to the client who is attempting to set the password for the channel.
 * @param addOrRemove A boolean value indicating whether the password should be added or removed from
 * the channel's mode. If it is true, the password will be added, and if it is false, the password will
 * be removed.
 * 
 * @return a boolean value.
 */
bool MODE::setPassword(Channel *channel, std::vector<std::string> params, Client *client, bool addOrRemove)
{
    if (params.size() > 2 && params[2].find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") != std::string::npos) {
        client->sendData(replies::ERR_BADCHANNELKEY(client, channel->getName()));
        return (false);
    }
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

/**
 * This function sets the user limit for a channel based on the parameters provided.
 * 
 * @param channel a pointer to a Channel object
 * @param client A pointer to a Client object representing the client who sent the MODE command.
 * @param params params is a vector of strings that contains the parameters passed to the function. The
 * first parameter is the mode being set, the second parameter is the channel name, and the third
 * parameter (if addOrRemove is true) is the user limit to be set.
 * @param addOrRemove A boolean value indicating whether the mode is being added or removed. If it's
 * true, the mode is being added. If it's false, the mode is being removed.
 * 
 * @return a boolean value.
 */
bool MODE::setUserLimit(Channel *channel, Client *client, std::vector<std::string> params, bool addOrRemove)
{
    if (addOrRemove && params.size() > 2)
    {
        if (params[2].find_first_not_of("0123456789") == std::string::npos)
        {
            std::stringstream sstream(params[2]);
            size_t limit;
            sstream >> limit;
            channel->setUserLimit(limit);
        }
        else
            return (false);
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
