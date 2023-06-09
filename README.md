# ft_irc

## Commands

Authentication:
- `CAP` -> no real implementation
- `PASS <password>`
- `NICK <nickname>`
- `USER <??>`

Basics:
- `PRIVMSG <reciever1, reciever2> <message>`
- `PING`
- `QUIT <~msg~>`

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

- what happens if too many paramters are passed to an command -> currently they are just ignored
- differentiate between trailing parameter and normal parameters -> after that the handling of the parameters count in the commands needs to be updated
- servername or host in replies??
- can receive privmsg before finished register!!
