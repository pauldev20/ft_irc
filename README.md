# ft_irc

## Commands

Authentication:
- `CAP` -> no real implementation
- `PASS <password>`
- `NICK <nickname>`
- `USER <username> <??> <??> :<fullname>` check also if its not empty -> shouldnt be empty

Basics:
- `PRIVMSG <reciever1, reciever2> :<message>` check also if its not empty -> shouldnt be empty
- `PING`
- `QUIT :<~msg~>` if trailing is empty return standard

Channels (user limits, passwords, invite-only):
- `JOIN <channel> <~password~>`
- `PART <channel1, channel2> :<reason>` if trailing is empty return standrd
- `KICK <channel1, channel2> <user1, user2> :<reason>` if trailing is empty return standrd
- `INVITE <nickname> <channel>`
- `TOPIC <channel> :<newtopic>` if trailing is empty delete topic
- `MODE <channel> <i, t, k, o, l>`
<!-- - `OPER <nickname> <password???>` -->


## WEECHAT Setup

1. `/server add <servername> <ip/hostname>/<port>`
2. `/set irc.server.<servername>.nicks "meinNick,meinNick2,meinNick3,meinNick4,meinNick5"`
3. `/set irc.server.<servername>.password "<password>"`
4. `/connect <servername>`
5. `/disconnect`

## TODO

- what happens if too many paramters are passed to an command -> currently they are just ignored
