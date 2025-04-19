/*
** EPITECH PROJECT, 2025
** Instructions
** File description:
** Send commands according to protocol
*/

#include "instructions.h"
#include "map.h"
#include "my_macros.h"
#include "player.h"
#include "server.h"
#include <bits/time.h>
#include <stdio.h>
#include <string.h>
#include <sys/poll.h>
#include <time.h>

const command_t commands[] = {
    {"PRESSED\r\n", move_up}, {"GETPOS\r\n", send_pos}, {NULL, NULL}};

static void send_death(server_t *server)
{
    const char msgWin[] = "WIN\r\n";
    const char msgLose[] = "LOSE\r\n";
    player_t *player = NULL;

    for (size_t i = 0; i < server->nb_player; i += 1) {
        player = server->players[i];
        if (player == NULL)
            return;
        if (player->is_alive == TRUE) {
            send(player->socket->fd, msgWin, strlen(msgWin), 0);
            continue;
        }
        send(player->socket->fd, msgLose, strlen(msgLose), 0);
    }
}

static void send_draw(server_t *server)
{
    const char msgDraw[] = "DRAW\r\n";

    if (server->players[1])
        send(server->players[1]->socket->fd, msgDraw, strlen(msgDraw), 0);
    if (server->players[0])
        send(server->players[0]->socket->fd, msgDraw, strlen(msgDraw), 0);
}

static void send_winner(server_t *server, size_t score1, size_t score2)
{
    const char msgWin[] = "WIN\r\n";
    const char msgLose[] = "LOSE\r\n";

    if (score1 > score2) {
        if (server->players[0])
            send(server->players[0]->socket->fd, msgWin, strlen(msgWin), 0);
        if (server->players[1])
            send(server->players[1]->socket->fd, msgLose, strlen(msgLose), 0);
        return;
    }
    if (score1 < score2) {
        if (server->players[1])
            send(server->players[1]->socket->fd, msgWin, strlen(msgWin), 0);
        if (server->players[0])
            send(server->players[0]->socket->fd, msgLose, strlen(msgLose), 0);
        return;
    }
    send_draw(server);
}

static void send_end(server_t *server)
{
    size_t score1 = 0;
    size_t score2 = 0;

    if (server->players[0])
        score1 = server->players[0]->score;
    if (server->players[1])
        score2 = server->players[1]->score;
    for (size_t i = 0; i < server->nb_player; i += 1)
        if (server->players[i]->is_alive == TRUE &&
            server->players[i]->ended != TRUE)
            return;
    send_winner(server, score1, score2);
}

static int check_collision(server_t *server, player_t *player)
{
    if (server->map[MAP_HEIGHT - 1 - (size_t)player->position.y]
        [(size_t)player->position.x] == 'e') {
        player->is_alive = FALSE;
        player->ended = TRUE;
        server->game_state = ENDED;
        send_death(server);
        return TRUE;
    }
    return FALSE;
}

static int check_early_return(server_t *server, player_t *player)
{
    if (player->ended == TRUE)
        return TRUE;
    if (server->game_state != STARTED)
        return TRUE;
    if (check_collision(server, player))
        return TRUE;
    return FALSE;
}

int execute_instructions(server_t *server, player_t *player, size_t i)
{
    const char unknown[] = "Unknown command";
    char buff[BUFFSIZE] = {0};
    size_t size_read = 0;

    size_read = read(player->socket->fd, buff, BUFFSIZE);
    if (size_read == 0) {
        server->remove_player(server, i);
        return FAILURE;
    }
    if (check_early_return(server, player) == TRUE)
        return SUCCESS;
    for (size_t i = 0; commands[i].name != NULL; i += 1) {
        if (strcmp(commands[i].name, buff) == 0) {
            commands[i].function(server, player);
            send_end(server);
            return SUCCESS;
        }
    }
    send(player->socket->fd, unknown, strlen(unknown), 0);
    return SUCCESS;
}
