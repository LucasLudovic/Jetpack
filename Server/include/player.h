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

typedef struct vector2_s {
    double x;
    double y;
} vector2_t;

typedef struct player_s {
    size_t score;
    int ended;
    uint8_t is_alive;
    vector2_t position;
    struct timespec time_last_ask;

    struct pollfd *socket;
} player_t;

player_t *create_player(struct pollfd *socket);

#endif /* ifndef PLAYER_H_ */
