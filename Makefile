##
## EPITECH PROJECT, 2019
## PSU_42sh_2018
## File description:
## Makefile
##

SRC	=	src/main.c	\
		src/utils/puts.c \
		src/tab_utils.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Iincl

NAME	=	42sh

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all