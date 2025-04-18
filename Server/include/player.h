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

typedef struct vector2_s {
    double x;
    double y;
} vector2_t;

typedef struct player_s {
    size_t score;
    int ended;
    uint8_t is_alive;
    vector2_t position;
    char *map[MAP_HEIGHT];
    struct timespec time_last_ask;

    struct pollfd *socket;
} player_t;

player_t *create_player(struct pollfd *socket);

#endif /* ifndef PLAYER_H_ */
