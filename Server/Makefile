##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile for server
##

SRC	=	src/main.c
SRC	+=	src/clean_up.c
SRC	+=	src/instructions.c
SRC	+=	src/player.c
SRC	+=	src/server.c
SRC	+=	src/server_init.c
SRC	+=	src/server_run.c
SRC	+=	src/map.c
SRC	+=	src/move.c


OBJ	=	$(SRC:.c=.o)

NAME	=	../jetpack_server

CC	=	gcc -g3

CFLAGS	=	-W -Wall -Wextra -Wpedantic

CPPFLAGS	=	-I include

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS)

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)

re: fclean all

debug: fclean $(OBJ)
	@$(CC) -g3 -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS)

.PHONY:	clean fclean re all
