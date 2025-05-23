/*
** EPITECH PROJECT, 2025
** cleanup
** File description:
** Free functions
*/

#include "cleanup.h"
#include "map.h"
#include "player.h"
#include "server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <unistd.h>

void simple_free(void **ptr)
{
    if (!ptr || !*ptr) {
        return;
    }
    free(*ptr);
    *ptr = NULL;
}

void free_server(server_t **server)
{
    if (!server || !(*server))
        return;
    if ((*server)->is_debug)
        printf("Server Cleanup\n");
    if ((*server)->map_file)
        free((*server)->map_file);
    if ((*server)->socket) {
        if ((*server)->socket->fd >= 0)
            close((*server)->socket->fd);
        free((*server)->socket);
    }
    if ((*server)->address)
        free((*server)->address);
    for (size_t i = 0; i < NB_PLAYER_MAX; i += 1)
        free_player((&(*server)->players[i]));
    free(*server);
    *server = NULL;
}

void free_player(player_t **player)
{
    if (player == NULL || *player == NULL) {
        return;
    }
    if ((*player)->socket) {
        if ((*player)->socket->fd >= 0) {
            close((*player)->socket->fd);
        }
        free((*player)->socket);
        (*player)->socket = NULL;
    }
    for (size_t i = 0; i < MAP_HEIGHT; i += 1) {
        if ((*player)->map[i]) {
            free((*player)->map[i]);
            (*player)->map[i] = NULL;
        }
    }
    free(*player);
    *player = NULL;
}
