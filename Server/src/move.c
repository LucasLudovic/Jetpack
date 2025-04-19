/*
** EPITECH PROJECT, 2025
** Move
** File description:
** Functions to move the player
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

static void check_line_coin(player_t *player, int line)
{
    const float hitbox_width = 0.7;
    const float left = player->position.x - (hitbox_width / 2.0);
    const float right = player->position.x + (hitbox_width / 2.0);
    const int start_x = (int)left;
    const size_t end_x = right < 0 ? 0 : (size_t)right;
    size_t map_y = 0;

    for (size_t x = start_x; x <= end_x; ++x) {
        if (line < 0 || x >= strlen(player->map[0]) || line >= MAP_HEIGHT)
            continue;
        map_y = MAP_HEIGHT - 1 - (size_t)line;
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

static void set_up_pos(
    server_t *server, player_t *player, long time_since_last_ask)
{
    player->position.y += 0.05 * time_since_last_ask;
    player->position.x += 0.02 * time_since_last_ask;
    if (player->position.y > MAP_HEIGHT - 1) {
        player->position.y = MAP_HEIGHT - 1;
    }
    if (player->position.x > strlen(server->map[0]) - 1) {
        player->position.x = strlen(server->map[0]) - 1;
        player->ended = TRUE;
    }
}

static void set_down_pos(
    server_t *server, player_t *player, long time_since_last_ask)
{
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
    }
}

void move_up(server_t *server, player_t *player)
{
    char buff[BUFFSIZE];
    struct timespec current_time = {0};
    long time_since_last_ask = 0;
    size_t score1 = 0;
    size_t score2 = 0;

    if (server->players[0])
        score1 = server->players[0]->score;
    if (server->players[1])
        score2 = server->players[1]->score;
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
    size_t score1 = 0;
    size_t score2 = 0;

    if (server->players[0])
        score1 = server->players[0]->score;
    if (server->players[1])
        score2 = server->players[1]->score;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    time_since_last_ask = compute_last_time(player, &current_time);
    set_down_pos(server, player, time_since_last_ask);
    check_coin(player);
    player->time_last_ask = current_time;
    snprintf(buff, BUFFSIZE, "position:x=%f:y=%f:s1=%zu,s2=%zu\r\n",
        player->position.x, player->position.y, score1, score2);
    send(player->socket->fd, buff, strlen(buff), 0);
}
