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

/**
 * @struct command_s
 * @brief Descriptor for a server command and its handler.
 *
 * @details
 * Associates a command name with the function that implements
 * its behavior, taking the server context and the target player
 * as parameters.
 */
typedef struct command_s {
    const char *name;
    void (*function)(server_t *server, player_t *player);
} command_t;

extern const command_t commands[];

/**
 * @brief Send current position and state to a player.
 *
 * Constructs a position update message and transmits it.
 *
 * @param server Server context.
 * @param player Target player.
 */
void send_pos(server_t *server, player_t *player);

/**
 * @brief Move the player's character upward.
 *
 * Applies velocity boost or upward movement per game physics.
 *
 * @param server Server context.
 * @param player Target player.
 */
void move_up(server_t *server, player_t *player);

/**
 * @brief Execute an instruction for one player.
 *
 * @param server Server context.
 * @param player Target player.
 * @param i      Index of the player in the server players list.
 * @return Number of instructions actually processed.
 */
int execute_instructions(server_t *server, player_t *player, size_t i);

#endif
