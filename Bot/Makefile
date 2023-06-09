# ---------------------------------------------------------------------------- #
#                                     BASE                                     #
# ---------------------------------------------------------------------------- #

NAME		:= ircbot
CC			:= c++
CPPFLAGS	:= -Wall -Wextra -Werror -std=c++98 #-fsanitize=address -g

# ----------------------------------- MAIN ----------------------------------- #
SRCFILES	:= main.cpp Bot.cpp

# ---------------------------------------------------------------------------- #
#                                     DIRS                                     #
# ---------------------------------------------------------------------------- #

OBJDIR		:= objs

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

OBJS		:= $(addprefix $(OBJDIR)/, $(SRCFILES:.cpp=.o))

# ----------------------------------- MAIN ----------------------------------- #

$(OBJDIR)/%.o: %.cpp
	@echo "$(GREEN)COMPILING:	$(HIGHIWHITE)$<...$(RESET)"
	@mkdir -p $(@D)
	@$(CC) $(INCLUDES) $(CPPFLAGS) -c $< -o $@

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

run: all
	@./$(NAME) 6667 1234 Bot

val: all
	@valgrind --leak-check=full ./$(NAME) 6667 1234 Bot

.PHONY: all clean fclean re debug run val
