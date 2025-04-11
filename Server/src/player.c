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
    player->is_alive = TRUE;
    player->score = 0;
    player->socket = socket;
    return player;
}
