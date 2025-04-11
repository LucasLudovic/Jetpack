/*
** EPITECH PROJECT, 2025
** Cleanup
** File description:
** Cleanup
*/

#ifndef CLEANUP_H_
    #define CLEANUP_H_

    #include "player.h"
#include "server.h"

void simple_free(void **ptr);

void free_server(server_t **server);

void free_player(player_t **client);

#endif /* ifndef CLEANUP_H_*/
