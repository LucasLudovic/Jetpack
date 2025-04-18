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
    if (player->position.x > strlen(server->map[0]) - 1) {
        player->position.x = strlen(server->map[0]) - 1;
        player->ended = TRUE;
    }
}

static void check_coin(
    server_t *server, player_t *player, vector2_t *last_position)
{
    if (server->map[(size_t)player->position.y][(size_t)player->position.x] ==
            'c' &&
        (size_t)last_position->x != (size_t)player->position.x &&
        (size_t)last_position->y != (size_t)player->position.y) {
        player->score += 1;
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

static int check_collision(
    server_t *server, player_t *player, vector2_t *last_position)
{
    if (server->map[(size_t)player->position.y][(size_t)player->position.x] ==
            'e' &&
        (size_t)last_position->x != (size_t)player->position.x &&
        (size_t)last_position->y != (size_t)player->position.y) {
        player->is_alive = FALSE;
        player->ended = TRUE;
        return TRUE;
    }
    return FALSE;
}

void move_up(server_t *server, player_t *player)
{
    char buff[BUFFSIZE];
    vector2_t last_position;
    struct timespec current_time = {0};
    long time_since_last_ask = 0;

    clock_gettime(CLOCK_MONOTONIC, &current_time);
    time_since_last_ask = compute_last_time(player, &current_time);
    if (player->ended == TRUE) {
        send(player->socket->fd, "GAME_END\r\n", strlen("GAME_END\r\n"), 0);
        return;
    }
    last_position.x = player->position.x;
    last_position.y = player->position.y;
    set_up_pos(server, player, time_since_last_ask);
    check_coin(server, player, &last_position);
    if (check_collision(server, player, &last_position) == TRUE) {
        send(player->socket->fd, "DIED\r\n", strlen("DIED\r\n"), 0);
        return;
    }
    player->time_last_ask = current_time;
    snprintf(buff, BUFFSIZE, "position:x=%f:y=%f\r\n", player->position.x,
        player->position.y);
    send(player->socket->fd, buff, strlen(buff), 0);
}

void send_pos(server_t *server, player_t *player)
{
    char buff[BUFFSIZE];
    struct timespec current_time = {0};
    vector2_t last_position;
    long time_since_last_ask = 0;

    clock_gettime(CLOCK_MONOTONIC, &current_time);
    time_since_last_ask = compute_last_time(player, &current_time);
    if (player->ended == TRUE) {
        send(player->socket->fd, "GAME_END\r\n", strlen("GAME_END\r\n"), 0);
        return;
    }
    last_position.x = player->position.x;
    last_position.y = player->position.y;
    set_down_pos(server, player, time_since_last_ask);
    check_coin(server, player, &last_position);
    player->time_last_ask = current_time;
    snprintf(buff, BUFFSIZE, "position:x=%f:y=%f\r\n", player->position.x,
        player->position.y);
    send(player->socket->fd, buff, strlen(buff), 0);
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
    if (server->game_state != STARTED)
        return SUCCESS;
    for (size_t i = 0; commands[i].name != NULL; i += 1) {
        if (strcmp(commands[i].name, buff) == 0) {
            commands[i].function(server, player);
            return SUCCESS;
        }
    }
    send(player->socket->fd, unknown, strlen(unknown), 0);
    return SUCCESS;
}
