# ft_irc

## Commands

Authentication:
- `CAP` -> no real implementation
- `PASS <password>`
- `NICK <nickname>`
- `USER <??>`

Basics:
- `PRIVMSG <nickname> <message>`
- `PING`

Channels (user limits, passwords, invite-only):
- `JOIN <channel> <~password~>`
- `PART <channel1, channel2> <reason>`
- `KICK <channel1, channel2> <user1, user2> <reason>`
- `INVITE <nickname> <channel>`
- `TOPIC <channel> <newtopic>` ?? can also read?
- `MODE <channel> <i, t, k, o, l>`
<!-- - `OPER <nickname> <password???>` -->


## WEECHAT Setup

1. `/server add <servername> <ip/hostname>/<port>`
2. `/set irc.server.<servername>.nicks "meinNick,meinNick2,meinNick3,meinNick4,meinNick5"`
3. `/set irc.server.<servername>.password "<password>"`
4. `/connect <servername>`
5. `/disconnect`

## TODO

- check whats up with `:/\0` in passwords and usernames??
- should a user be still operator after getting kicked
- send all messages in a channel to all users??? JOIN, QUIT, PART???