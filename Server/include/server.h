/*
** EPITECH PROJECT, 2025
** server
** File description:
** Server struct with basic functions
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <stddef.h>
    #include "player.h"

    #define NB_PLAYER_MAX 10

typedef struct server_s {
    int socket;
    size_t nb_player;
    player_t players[NB_PLAYER_MAX];
    char *mapFile;

    int (*run)(void);
} server_t;

#endif /* ifndef SERVER_H_ */
