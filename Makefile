##
## EPITECH PROJECT, 2023
## make create
## File description:
## make
##

all: client server

server:
	make -C Server

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
