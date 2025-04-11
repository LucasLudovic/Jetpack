##
## EPITECH PROJECT, 2023
## make create
## File description:
## make
##

all: client server

<<<<<<< HEAD
server:
	make -C Server
=======
SERVER_SRC	=	Server/src/main.c
SERVER_SRC	+=	Server/src/server.c
SERVER_SRC	+=	Server/src/server_init.c
SERVER_SRC	+=	Server/src/clean_up.c
SERVER_SRC	+=	Server/src/instructions.c
SERVER_SRC	+=	Server/src/player.c
SERVER_SRC	+=	Server/src/server_run.c

SERVER_OBJ	=	$(SERVER_SRC:.c=.o)

SERVER_CC	=	gcc

SERVER_NAME	=	jetpack_server

CC	=	gcc -g3

$(SERVER_NAME): $(SERVER_OBJ)
	$(CC) -o $(SERVER_NAME) $(SERVER_OBJ) $(CFLAGS) $(CPPFLAGS)


CLIENT_SRC	=	Client/src/main.cpp

CLIENT_OBJ	=	$(CLIENT_SRC:.cpp=.o)

CLIENT_CC	=	g++

CLIENT_NAME	=	jetpack_client

CXX = g++

$(CLIENT_NAME): $(CLIENT_OBJ)
	$(CXX) -o $(CLIENT_NAME) $(CLIENT_OBJ) $(CFLAGS)

client: $(CLIENT_NAME)

server: $(SERVER_NAME)

CFLAGS	=	-W -Wall -Wextra -Wpedantic

CPPFLAGS = -I Server/include
>>>>>>> 0bf2ce2 (feat(server): multi connection and disconnection for player)

client:
	make -C Client

clean:
	@make clean -C Client
	@make clean -C Server

fclean: clean
	@make fclean -C Client
	@make fclean -C Server

re: fclean all

.PHONY:	all clean fclean re server client
