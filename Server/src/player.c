/*
** EPITECH PROJECT, 2025
** player
** File description:
** Implémentation of base struct for player
*/

#include "player.h"
#include "map.h"
#include "my_macros.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

player_t *create_player(struct pollfd *socket)
{
    player_t *player = malloc(sizeof(player_t));

    if (!player) {
        fprintf(stderr, "Unable to alloc player");
        return NULL;
    }
    player->time_last_ask.tv_nsec = 0;
    player->time_last_ask.tv_sec = 0;
    player->ended = FALSE;
    player->is_alive = TRUE;
    player->score = 0;
    player->socket = socket;
    player->position.x = 0;
    player->position.y = 0;
    for (size_t i = 0; i < MAP_HEIGHT; i += 1) {
        player->map[i] = NULL;
    }
    return player;
}
