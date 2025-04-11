/*
** EPITECH PROJECT, 2025
** player
** File description:
** Player struct with basic functions
*/

#ifndef PLAYER_H_
    #define PLAYER_H_

    #include <netinet/in.h>
    #include <stdint.h>
    #include <stddef.h>

typedef struct player_s {
    size_t score;
    uint8_t is_alive;

    struct pollfd *socket;
} player_t;

player_t *create_player(struct pollfd *socket);

#endif /* ifndef PLAYER_H_ */
