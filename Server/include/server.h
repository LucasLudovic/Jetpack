/*
** EPITECH PROJECT, 2025
** server
** File description:
** Server struct with basic functions
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include "player.h"
    #include <stddef.h>
    #include <unistd.h>

    #define NB_PLAYER_MAX 2

typedef struct server_s {
    int is_debug;
    int is_running;
    char *map_file;

    struct pollfd *socket;
    struct sockaddr_in *address;
    int port;
    socklen_t socklen;

    size_t nb_player;
    player_t players[NB_PLAYER_MAX];

    int (*run)(struct server_s *this);
    void (*destroy)(struct server_s **this);
} server_t;

server_t *create_server(int port, const char *map, int debug);

#endif /* ifndef SERVER_H_ */
