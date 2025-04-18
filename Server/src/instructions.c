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

static void set_up_pos(
    server_t *server, player_t *player, long time_since_last_ask)
{
    char msg[BUFFSIZE] = {0};
    const size_t p1_score = server->players[0] ? server->players[0]->score : 0;
    const size_t p2_score = server->players[1] ? server->players[1]->score : 0;

    player->position.y += 0.05 * time_since_last_ask;
    player->position.x += 0.02 * time_since_last_ask;
    if (player->position.y > MAP_HEIGHT - 1) {
        player->position.y = MAP_HEIGHT - 1;
    }
    if (player->position.x > strlen(server->map[0]) - 1) {
        player->position.x = strlen(server->map[0]) - 1;
        player->ended = TRUE;
        snprintf(
            msg, BUFFSIZE, "GAME_END:p1%lu:p2%lu\r\n", p1_score, p2_score);
        send(player->socket->fd, msg, strlen(msg), 0);
    }
}

static void set_down_pos(
    server_t *server, player_t *player, long time_since_last_ask)
{
    char msg[BUFFSIZE] = {0};
    const size_t p1_score = server->players[0] ? server->players[0]->score : 0;
    const size_t p2_score = server->players[1] ? server->players[1]->score : 0;

    player->position.y -= 0.05 * time_since_last_ask;
    player->position.x += 0.02 * time_since_last_ask;
    if (player->position.y < 0)
        player->position.y = 0;
    if (player->position.y >= MAP_HEIGHT - 1) {
        player->position.y = MAP_HEIGHT - 1;
    }
    if (player->position.x > (double)strlen(server->map[0]) - 1) {
        player->position.x = (double)strlen(server->map[0]) - 1;
        player->ended = TRUE;
        snprintf(
            msg, BUFFSIZE, "GAME_END:p1%lu:p2%lu\r\n", p1_score, p2_score);
        send(player->socket->fd, msg, strlen(msg), 0);
    }
}

static void check_line_coin(player_t *player, int line)
{
    const float hitbox_width = 0.7;
    const float left = player->position.x - (hitbox_width / 2.0);
    const float right = player->position.x + (hitbox_width / 2.0);
    const int start_x = (int)left;
    const size_t end_x = right < 0 ? 0 : (size_t)right;

    for (size_t x = start_x; x <= end_x; ++x) {
        if (line < 0 || x >= strlen(player->map[0]) || line >= MAP_HEIGHT)
            continue;

        size_t map_y = MAP_HEIGHT - 1 - (size_t)line;
        if (player->map[map_y][x] == 'c') {
            player->map[map_y][x] = '_';
            player->score += 1;
        }
    }
}

static void check_coin(player_t *player)
{
    const float hitbox_height = 0.7;
    const float bottom = player->position.y - (hitbox_height / 2.0);
    const float top = player->position.y + (hitbox_height / 2.0);
    const int start_y = (int)bottom;
    const int end_y = (int)top;

    for (int y = start_y; y <= end_y; ++y) {
        check_line_coin(player, y);
    }
}

static long compute_last_time(player_t *player, struct timespec *current_time)
{
    long time_since_last_ask = 0;

    time_since_last_ask =
        ((current_time->tv_sec - player->time_last_ask.tv_sec) * 1000) +
        ((current_time->tv_nsec - player->time_last_ask.tv_nsec) / 1000000);
    time_since_last_ask /= 10;
    return time_since_last_ask;
}

static void send_death(server_t *server)
{
    const char msgWin[] = "WIN\r\n";
    const char msgLose[] = "LOSE\r\n";
    player_t *player = NULL;

    if (server->game_state != ENDED) {
        return;
    }
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

static void send_end(server_t *server)
{
    const char msgWin[] = "WIN\r\n";
    const char msgLose[] = "LOSE\r\n";
    const char msgDraw[] = "DRAW\r\n";
    const size_t score1 = server->players[0]->score;
    const size_t score2 = server->players[1]->score;

    for (size_t i = 0; i < server->nb_player; i += 1) {
        if (server->players[i]->is_alive == TRUE)
            return;
    }
    if (score1 > score2) {
        send(server->players[0]->socket->fd, msgWin, strlen(msgWin), 0);
        send(server->players[1]->socket->fd, msgLose, strlen(msgLose), 0);
        return;
    }
    if (score1 < score2) {
        send(server->players[1]->socket->fd, msgWin, strlen(msgWin), 0);
        send(server->players[0]->socket->fd, msgLose, strlen(msgLose), 0);
        return;
    }
    send(server->players[1]->socket->fd, msgDraw, strlen(msgDraw), 0);
    send(server->players[0]->socket->fd, msgDraw, strlen(msgDraw), 0);
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

void move_up(server_t *server, player_t *player)
{
    char buff[BUFFSIZE];
    struct timespec current_time = {0};
    long time_since_last_ask = 0;
    size_t score1 = server->players[0]->score;
    size_t score2 = server->players[1]->score;

    clock_gettime(CLOCK_MONOTONIC, &current_time);
    time_since_last_ask = compute_last_time(player, &current_time);
    set_up_pos(server, player, time_since_last_ask);
    check_coin(player);
    player->time_last_ask = current_time;
    snprintf(buff, BUFFSIZE, "position:x=%f:y=%f:s1=%zu,s2=%zu\r\n",
        player->position.x, player->position.y, score1, score2);
    send(player->socket->fd, buff, strlen(buff), 0);
}

void send_pos(server_t *server, player_t *player)
{
    char buff[BUFFSIZE];
    struct timespec current_time = {0};
    long time_since_last_ask = 0;

    clock_gettime(CLOCK_MONOTONIC, &current_time);
    time_since_last_ask = compute_last_time(player, &current_time);
    set_down_pos(server, player, time_since_last_ask);
    check_coin(player);
    player->time_last_ask = current_time;
    snprintf(buff, BUFFSIZE, "position:x=%f:y=%f:s=%zu\r\n",
        player->position.x, player->position.y, player->score);
    send(player->socket->fd, buff, strlen(buff), 0);
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
            return SUCCESS;
        }
    }
    send_death(server);
    send(player->socket->fd, unknown, strlen(unknown), 0);
    return SUCCESS;
}
