# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/22 17:21:47 by pgeeser           #+#    #+#              #
#    Updated: 2023/06/23 19:23:32 by pgeeser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#                                     BASE                                     #
# ---------------------------------------------------------------------------- #

NAME		:= ircserv
BOTNAME		:= ircbot
CC			:= c++
CPPFLAGS	:= -Wall -Wextra -Werror -std=c++98 #-fsanitize=address -g

INCLUDES	:= -I./includes

# ----------------------------------- MAIN ----------------------------------- #
SRCFILES	:= main.cpp Server.cpp Client.cpp Message.cpp Parser.cpp Executer.cpp Debug.cpp Channel.cpp

# ----------------------------------- CMDs ----------------------------------- #
SRCFILES	+= cmds/Command.cpp cmds/Replies.cpp cmds/CAP.cpp cmds/PASS.cpp \
			   cmds/NICK.cpp cmds/USER.cpp cmds/PING.cpp cmds/QUIT.cpp \
			   cmds/PRIVMSG.cpp cmds/JOIN.cpp cmds/PART.cpp cmds/MODE.cpp \
			   cmds/TOPIC.cpp cmds/INVITE.cpp cmds/KICK.cpp\

# ------------------------------------ BOT ----------------------------------- #
BOTFILES	:= bot/main.cpp bot/Bot.cpp

# ---------------------------------------------------------------------------- #
#                                     DIRS                                     #
# ---------------------------------------------------------------------------- #

OBJDIR		:= objs
SRCDIR		:= srcs

# ---------------------------------------------------------------------------- #
#                                    COLORS                                    #
# ---------------------------------------------------------------------------- #

RED			:=	\033[0;31m
GREEN		:=	\033[0;32m
BLUE		:=	\033[0;34m
HIGHIWHITE	:=	\033[0;39m
RESET		:=	\033[0m

# ---------------------------------------------------------------------------- #
#                                     VARS                                     #
# ---------------------------------------------------------------------------- #

SRCFILES	:= $(addprefix $(SRCDIR)/, $(SRCFILES))
OBJS		:= $(addprefix $(OBJDIR)/, $(SRCFILES:.cpp=.o))
BOTFILES	:= $(addprefix $(SRCDIR)/, $(BOTFILES))
BOTOBJS		:= $(addprefix $(OBJDIR)/, $(BOTFILES:.cpp=.o))

# ----------------------------------- MAIN ----------------------------------- #

$(OBJDIR)/%.o: %.cpp
	@echo "$(GREEN)COMPILING:	$(HIGHIWHITE)$<...$(RESET)"
	@mkdir -p $(@D)
	@$(CC) $(INCLUDES) $(CPPFLAGS) -c $< -o $@

$(NAME) $(BOTNAME): $(OBJS) $(BOTOBJS)
	@echo "$(BLUE)LINKING:	$(HIGHIWHITE)$(NAME)$(RESET)"
	@$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)OUTPUT:		$(NAME)$(RESET)"
	@echo "$(BLUE)LINKING:	$(HIGHIWHITE)$(BOTNAME)$(RESET)"
	@$(CC) $(CPPFLAGS) $(BOTOBJS) -o $(BOTNAME)
	@echo "$(GREEN)OUTPUT:		$(BOTNAME)$(RESET)"

# ----------------------------------- OTHER ---------------------------------- #

all: $(NAME) $(BOTNAME)

clean:
	@echo "$(RED)CLEANING...$(RESET)"
	@rm -rf $(OBJS)
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(BOTNAME)

re: fclean
	@$(MAKE) all

debug:
	$(MAKE) CPPFLAGS='-g' re

run: all
	@./$(NAME) 6667 1234

val: all
	@valgrind --leak-check=full ./$(NAME) 1233 1234

.PHONY: all clean fclean re debug run val
