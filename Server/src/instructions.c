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

void move_up(server_t *server, player_t *player)
{
    char buff[BUFFSIZE];
    struct timespec current_time = {0};
    long time_since_last_ask = 0;

    clock_gettime(CLOCK_MONOTONIC, &current_time);

    time_since_last_ask =
        ((current_time.tv_sec - player->time_last_ask.tv_sec) * 1000) +
        ((current_time.tv_nsec - player->time_last_ask.tv_nsec) / 1000000);
    time_since_last_ask /= 100;

    if (player->ended == TRUE) {
        send(player->socket->fd, "GAME_END", strlen("GAME_END"), 0);
        return;
    }

    player->position.y += 0.1 * time_since_last_ask;
    player->position.x += 0.1 * time_since_last_ask;

    if (player->position.y >= MAP_HEIGHT - 1) {
        player->position.y = MAP_HEIGHT - 1;
    }
    if (player->position.x >= strlen(server->map[0])) {
        player->position.x = strlen(server->map[0]) - 1;
        player->ended = TRUE;
    }
    player->time_last_ask = current_time;
    snprintf(buff, BUFFSIZE, "position:x=%f:y%f\n", player->position.x,
        player->position.y);
    send(player->socket->fd, buff, strlen(buff), 0);
}

void send_pos(server_t *server, player_t *player)
{
    char buff[BUFFSIZE];
    struct timespec current_time = {0};
    long time_since_last_ask = 0;

    clock_gettime(CLOCK_MONOTONIC, &current_time);

    time_since_last_ask =
        ((current_time.tv_sec - player->time_last_ask.tv_sec) * 1000) +
        ((current_time.tv_nsec - player->time_last_ask.tv_nsec) / 1000000);
    time_since_last_ask /= 100;

    if (player->ended == TRUE) {
        send(player->socket->fd, "GAME_END", strlen("GAME_END"), 0);
        return;
    }
    player->position.y -= 0.05 * time_since_last_ask;
    player->position.x += 0.1 * time_since_last_ask;

    if (player->position.y < 0)
        player->position.y = 0;
    if (player->position.y >= MAP_HEIGHT - 1) {
        player->position.y = MAP_HEIGHT - 1;
    }
    if (player->position.x >= strlen(server->map[0])) {
        player->position.x = strlen(server->map[0]) - 1;
        player->ended = TRUE;
    }
    player->time_last_ask = current_time;
    snprintf(buff, BUFFSIZE, "position:x=%f:y%f\n", player->position.x,
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
    printf("Command: %s\n", buff);
    send(player->socket->fd, unknown, strlen(unknown), 0);
    return SUCCESS;
}
