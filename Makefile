# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/22 17:21:47 by pgeeser           #+#    #+#              #
#    Updated: 2023/06/04 15:50:19 by pgeeser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#                                     BASE                                     #
# ---------------------------------------------------------------------------- #

NAME		:= ircserv
CC			:= c++
CPPFLAGS	:= -Wall -Wextra -Werror -std=c++98 -fsanitize=address

SRCFILES	:= main.cpp Server.cpp Client.cpp Parser.cpp Command.cpp Executer.cpp Debug.cpp Channel.cpp

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

# ----------------------------------- MAIN ----------------------------------- #

$(OBJDIR)/%.o: %.cpp
	@echo "$(GREEN)COMPILING:	$(HIGHIWHITE)$<...$(RESET)"
	@mkdir -p $(@D)
	@$(CC) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(BLUE)LINKING:	$(HIGHIWHITE)$(NAME)$(RESET)"
	@$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)OUTPUT:		$(NAME)$(RESET)"

# ----------------------------------- OTHER ---------------------------------- #

all: $(NAME)

clean:
	@echo "$(RED)CLEANING...$(RESET)"
	@rm -rf $(OBJS)
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	@$(MAKE) all

debug:
	$(MAKE) CPPFLAGS='-g' re

.PHONY: all clean fclean re debug
