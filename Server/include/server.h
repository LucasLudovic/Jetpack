/*
** EPITECH PROJECT, 2025
** server
** File description:
** Server struct with basic functions
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <stddef.h>
    #include <unistd.h>
    #include "player.h"

    #define NB_PLAYER_MAX 2

typedef struct server_s {
    struct pollfd *socket;
    struct sockaddr_in *address;
    int port;
    socklen_t socklen;
    size_t nb_player;
    player_t players[NB_PLAYER_MAX];
    char *map_file;
    int is_debug;

    int (*run)(struct server_s *this);
    void (*destroy)(struct server_s **this);
} server_t;

server_t *create_server(int port, const char *map, int debug);

#endif /* ifndef SERVER_H_ */
