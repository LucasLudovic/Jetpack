/*
** EPITECH PROJECT, 2025
** player
** File description:
** Player struct with basic functions
*/

#ifndef PLAYER_H_
    #define PLAYER_H_

    #include <stddef.h>

typedef struct player_s {
    int socket;
    size_t score;
} player_t;

#endif /* ifndef PLAYER_H_ */
