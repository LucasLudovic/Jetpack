/*
** EPITECH PROJECT, 2025
** Map
** File description:
** Send map to client
*/

#include "my_macros.h"
#include "player.h"
#include "server.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <unistd.h>

void send_map(server_t *server)
{
    char *buff = NULL;
    size_t size_read = 0;
    FILE *file = fopen(server->map_file, "r");

    if (file == NULL) {
        server->destroy(&server);
        exit(EPITECH_FAILURE);
    }
    while (getline(&buff, &size_read, file) >= 0) {
        for (size_t i = 0; i < server->nb_player; i += 1) {
            server->send(server->players[i], buff);
        }
        if (buff != NULL) {
            free(buff);
            buff = NULL;
        }
    }
    for (size_t i = 0; i < server->nb_player; i += 1) {
        server->send(server->players[i], "Map sent");
    }
}
