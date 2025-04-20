/*
** EPITECH PROJECT, 2025
** Map
** File description:
** Header for map commands
*/

#ifndef MAP_H_
    #define MAP_H_
    #include <stddef.h>

    #define MAP_HEIGHT 10
    #define MAP_LENGTH_MAX 10000

typedef struct server_s server_t;

/**
 * @brief Load the game map into server memory.
 *
 * Reads map file specified in server->map_file,
 * populates server->map array, and validates dimensions.
 *
 * @param server Server instance to load map into.
 */
void load_map(server_t *server);

#endif
