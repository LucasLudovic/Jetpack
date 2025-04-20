/*
** EPITECH PROJECT, 2025
** player
** File description:
** Player struct with basic functions
*/

#ifndef PLAYER_H_
    #define PLAYER_H_

    #include "map.h"
    #include <netinet/in.h>
    #include <stddef.h>
    #include <stdint.h>

/**
 * @struct vector2_s
 * @brief Représente un vecteur 2D à virgule flottante.
 *
 * Chaque composante est un double, utilisé pour stocker
 * la position dans le jeu.
 */
typedef struct vector2_s {
    double x;
    double y;
} vector2_t;

/**
 * @struct player_s
 * @brief Represents a connected player in the game server.
 *
 * @details
 * Tracks the player's game state, position, and communication socket.
 */
typedef struct player_s {
    size_t score;
    int ended;
    uint8_t is_alive;
    vector2_t position;
    char *map[MAP_HEIGHT];
    struct timespec time_last_ask;

    struct pollfd *socket;
} player_t;

/**
 * @brief Allocate and initialize a new player.
 *
 * Creates a player_t, assigns the given socket descriptor,
 * initializes default state, and returns the instance.
 *
 * @param socket Pointer to the pollfd for the new connection.
 * @return Pointer to newly created player_t, or NULL on failure.
 */
player_t *create_player(struct pollfd *socket);

#endif /* ifndef PLAYER_H_ */
