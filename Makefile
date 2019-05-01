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
		$(SRC_DIR)/utils/puts.c	\
		$(SRC_DIR)/utils/tab_utils.c	\
		$(SRC_DIR)/utils/verif_malloc.c \

debug:			CFLAGS += -g

all:	$(OBJ_DIR) $(NAME) lol

lol:
	@printf "****************************************\n"
	@printf "* $(RED)██╗  ██╗$(BLUE)██████╗     $(ORANGE)███████╗$(GREEN)██╗  ██╗ $(WHITE)*\n"
	@printf "* $(RED)██║  ██║$(BLUE)╚════██╗    $(ORANGE)██╔════╝$(GREEN)██║  ██║ $(WHITE)*\n"
	@printf "* $(RED)███████║$(BLUE) █████╔╝    $(ORANGE)███████╗$(GREEN)███████║ $(WHITE)*\n"
	@printf "* $(RED)╚════██║$(BLUE)██╔═══╝     $(ORANGE)╚════██║$(GREEN)██╔══██║ $(WHITE)*\n"
	@printf "* $(RED)     ██║$(BLUE)███████╗    $(ORANGE)███████║$(GREEN)██║  ██║ $(WHITE)*\n"
	@printf "* $(RED)     ╚═╝$(BLUE)╚══════╝    $(ORANGE)╚══════╝$(GREEN)╚═╝  ╚═╝ $(WHITE)*\n"
	@printf "****************************************\n"
	@printf "$(PWD)> "
	@sleep 0.2
	@printf "r"
	@sleep 0.2
	@printf "m"
	@sleep 0.2
	@printf " "
	@sleep 0.2
	@printf "-"
	@sleep 0.2
	@printf "r"
	@sleep 0.2
	@printf "f"
	@sleep 0.2
	@printf " "
	@sleep 0.2
	@printf "/"
	@printf "\n"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@mkdir $(OBJ_DIR)/utils

OBJ	=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
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
