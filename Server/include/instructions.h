/*
** EPITECH PROJECT, 2025
** Instructions
** File description:
** Header for communication between server and player
*/

#ifndef INSTRUCTIONS_H_
    #define INSTRUCTIONS_H_

    #include "server.h"
    #include "player.h"

typedef struct command_s {
    const char *name;
    void (*function)(server_t *server, player_t *player);
} command_t;

extern const command_t commands[];

void send_pos(server_t *server, player_t *player);
void move_up(server_t *server, player_t *player);
int execute_instructions(server_t *server, player_t *player, size_t i);

#endif
