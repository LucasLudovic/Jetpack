/*
** EPITECH PROJECT, 2025
** Cleanup
** File description:
** Cleanup
*/

#ifndef CLEANUP_H_
    #define CLEANUP_H_

    #include "player.h"
    #include "server.h"

/**
 * @brief Safely free a dynamically allocated pointer and NULL it.
 *
 * @param ptr Double-pointer to the memory to free.
 */
void simple_free(void **ptr);

/**
 * @brief Destroy and free a server instance.
 *
 * Invokes the server's destroy method, closes sockets,
 * frees resources, and sets the pointer to NULL.
 *
 * @param server Double-pointer to the server_t instance.
 */
void free_server(server_t **server);


/**
 * @brief Destroy and free a player instance.
 *
 * Cleans up player resources such as buffers and sockets,
 * then frees the structure and sets the pointer to NULL.
 *
 * @param player Double-pointer to the player_t instance.
 */
void free_player(player_t **player);

#endif /* ifndef CLEANUP_H_*/
