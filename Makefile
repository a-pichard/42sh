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

TESTS_DIR	=	tests/unit_test
MAIN	=	main.c
SRC_TESTS	=	$(shell find $(SRC_DIR) $(TESTS_DIR) -type f -name '*.c' -not -path $(SRC_DIR)/$(MAIN) 2> /dev/null)
SRC	=	$(shell find $(SRC_DIR)/ -type f -name '*.c')

all:	$(NAME) lol

debug: fclean $(eval CFLAGS	+=	-g) $(NAME)

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
	@$(CC) -o $(NAME) $^


tests_run:
	@$(V)$(CC) $(CFLAGS) $(SRC_TESTS) -o unit_test -Iinclude -lcriterion --coverage $(LDFLAGS)
	printf "$(BLUE)Compile sources and tests : $(GREEN)success$(WHITE)\n"
	printf "$(BLUE)Launching tests...$(WHITE)\n"
	./unit_test
	gcovr --branches --exclude tests

clean:
	@rm -Rf $(OBJ_DIR)
	@printf "$(RED)clean$(WHITE)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)fclean$(WHITE)\n"

re: fclean all

.PHONE: all clean fclean re lol
