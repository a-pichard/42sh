##
## EPITECH PROJECT, 2019
## vm makefile
## File description:
## Makefile
##

ROOT	=	.
NAME	=	42sh
RM	=	rm -f
INCL_DIR	=	$(ROOT)/incl
OBJ_DIR	= $(ROOT)/obj
SRC_DIR	= $(ROOT)/src
CFLAGS = -Wall -Wextra -I$(INCL_DIR)
CC	=	gcc

GREEN	=	\e[1;32m
WHITE	=	\e[0m
ORANGE	=	\e[1;33m
RED	=	\e[1;35m
BLUE	=	\e[1;34m

SRC	=	$(SRC_DIR)/main.c	\
		$(SRC_DIR)/my_shell.c	\
		$(SRC_DIR)/prompt.c	\
		$(SRC_DIR)/utils/vec/apply.c	\
		$(SRC_DIR)/builtin/pars_env.c	\
		$(SRC_DIR)/utils/vec/create.c	\
		$(SRC_DIR)/utils/vec/destroy.c	\
		$(SRC_DIR)/utils/vec/get.c	\
		$(SRC_DIR)/utils/vec/pop.c	\
		$(SRC_DIR)/utils/vec/push.c	\
		$(SRC_DIR)/utils/vec/set.c	\
		$(SRC_DIR)/utils/str/my_str_to_word_tab_plus.c	\
		$(SRC_DIR)/utils/puts.c	\
		$(SRC_DIR)/utils/tab_utils.c	\
		$(SRC_DIR)/utils/verif_malloc.c \
		$(SRC_DIR)/utils/my_atoi.c	\
		$(SRC_DIR)/utils/index_of.c	\
		$(SRC_DIR)/utils/str/my_strcat.c	\
		$(SRC_DIR)/builtin/cd.c	\
		$(SRC_DIR)/builtin/cd_with_args.c	\
		$(SRC_DIR)/builtin/echo.c	\
		$(SRC_DIR)/builtin/env.c	\
		$(SRC_DIR)/builtin/exit.c	\
		$(SRC_DIR)/builtin/setenv.c	\
		$(SRC_DIR)/builtin/unsetenv.c	\
		$(SRC_DIR)/signal.c	\
		$(SRC_DIR)/command.c

all:	$(NAME) lol

debug: val $(NAME)

val:
        $(eval CFLAGS	+=	-g)

lol:
	@printf "****************************************\n"
	@printf "* $(RED)██╗  ██╗$(BLUE)██████╗     $(ORANGE)███████╗$(GREEN)██╗  ██╗ $(WHITE)*\n"
	@printf "* $(RED)██║  ██║$(BLUE)╚════██╗    $(ORANGE)██╔════╝$(GREEN)██║  ██║ $(WHITE)*\n"
	@printf "* $(RED)███████║$(BLUE) █████╔╝    $(ORANGE)███████╗$(GREEN)███████║ $(WHITE)*\n"
	@printf "* $(RED)╚════██║$(BLUE)██╔═══╝     $(ORANGE)╚════██║$(GREEN)██╔══██║ $(WHITE)*\n"
	@printf "* $(RED)     ██║$(BLUE)███████╗    $(ORANGE)███████║$(GREEN)██║  ██║ $(WHITE)*\n"
	@printf "* $(RED)     ╚═╝$(BLUE)╚══════╝    $(ORANGE)╚══════╝$(GREEN)╚═╝  ╚═╝ $(WHITE)*\n"
	@printf "****************************************\n"

OBJ	=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(RED)[$(BLUE)$<$(RED)]$(WHITE)"
	@printf "\t->\t"
	@printf "$(RED)[$(GREEN)$@$(RED)]$(WHITE)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	:	$(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $^

clean:
	@rm -Rf $(OBJ_DIR)
	@printf "$(RED)clean$(WHITE)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)fclean$(WHITE)\n"

re: fclean all

.PHONE: all clean fclean re lol
