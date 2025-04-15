/*
** EPITECH PROJECT, 2025
** player
** File description:
** Implémentation of base struct for player
*/

#include "player.h"
#include "my_macros.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

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
    return player;
}
