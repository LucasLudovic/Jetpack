/*
** EPITECH PROJECT, 2025
** Instructions
** File description:
** Send commands according to protocol
*/

#include "server.h"
#include "player.h"
#include "my_macros.h"
#include <stdio.h>
#include <sys/poll.h>

int execute_instructions(server_t *server, player_t *player, size_t i)
{
    char buff[BUFFSIZE] = {0};
    size_t size_read = 0;

    size_read = read(player->socket->fd, buff, BUFFSIZE);
    if (size_read == 0) {
        server->remove_player(server, i);
        return FAILURE;
    }
    if (server->game_state != STARTED)
        return SUCCESS;
    return SUCCESS;
}
