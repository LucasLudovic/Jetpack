##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile for client
##

SRC	=	./src/main.cpp
SRC	+=	./src/client.cpp
SRC	+=	./src/JetpackClient/JetpackClient.cpp
SRC	+=	./src/Network/Network.cpp
SRC	+=	./src/Network/socket/Socket.cpp
SRC	+=	./src/Display/Display.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	../jetpack_client

CC	=	g++

CFLAGS	=	-W -Wall -Wextra -Wpedantic

SFML = -lsfml-graphics -lsfml-window -lsfml-system

CPPFLAGS	=	-I src

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS) $(SFML)

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)

re: fclean all

debug: fclean $(OBJ)
	@$(CC) -g3 -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS)

.PHONY:	clean fclean re all
