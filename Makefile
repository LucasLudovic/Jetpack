##
## EPITECH PROJECT, 2023
## make create
## File description:
## make
##

all: server client

SERVER_SRC	=	Server/src/main.c

SERVER_OBJ	=	$(SERVER_SRC:.c=.o)

SERVER_CC	=	gcc

SERVER_NAME	=	jetpack_server

CC	=	gcc

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


clean:
	@rm -f $(SERVER_OBJ)
	@rm -f $(CLIENT_OBJ)
	@find . -name "*~" -delete

fclean: clean
	@rm -f $(SERVER_NAME)
	@rm -f $(CLIENT_NAME)
	@find . -name "*.gcda" -delete
	@find . -name "*.gcno" -delete

re: fclean all

.PHONY:	all clean fclean re server client
