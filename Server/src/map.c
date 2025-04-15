/*
** EPITECH PROJECT, 2025
** Map
** File description:
** Send map to client
*/

#include "map.h"
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
    if (!server) {
        fprintf(stderr, "Can't use server to send map\n");
        server->destroy(&server);
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < MAP_HEIGHT; i += 1) {
        if (!server->map[i]) {
            fprintf(stderr, "Server map is empty\n");
            server->destroy(&server);
            exit(EXIT_FAILURE);
        }
        for (size_t j = 0; j < server->nb_player; j += 1) {
            if (send(server->players[j]->socket->fd, server->map[i],
                    strlen(server->map[i]), 0) == 1) {
                fprintf(stderr, "Unable to send map\n");
                server->destroy(&server);
                exit(EXIT_FAILURE);
            }
        }
    }
}

void load_map(server_t *server)
{
    char *buff = NULL;
    size_t size_read = 0;
    FILE *file = fopen(server->map_file, "r");
    size_t nb_lines = 0;

    if (file == NULL) {
        fprintf(stderr, "Unable to open the map\n");
        server->destroy(&server);
        exit(EPITECH_FAILURE);
    }
    while (getline(&buff, &size_read, file) > 0) {
        if (strlen(buff) > MAP_LENGTH_MAX) {
            fprintf(stderr, "Map too long\n");
            server->destroy(&server);
            exit(EXIT_FAILURE);
        }
        if (buff[strlen(buff) - 1] == '\n') {
            buff[strlen(buff) - 1] = '\0';
        }
        if (nb_lines > 0) {
            if (strlen(buff) != strlen(server->map[nb_lines - 1])) {
                fprintf(stderr,
                    "Map with inconsistent length: %zu, %zu, %zu\n", nb_lines,
                    strlen(buff), strlen(server->map[nb_lines - 1]));
                server->destroy(&server);
                exit(EXIT_FAILURE);
            }
        }
        if (nb_lines == MAP_HEIGHT) {
            printf("Map: %s\n", buff);
            fprintf(stderr, "Map with incorrect height\n");
            server->destroy(&server);
            exit(EXIT_FAILURE);
        }
        server->map[nb_lines] = strdup(buff);
        nb_lines += 1;
        if (buff != NULL) {
            free(buff);
            buff = NULL;
        }
    }
    if (nb_lines != MAP_HEIGHT) {
        fprintf(stderr, "Unable to open the map\n");
        server->destroy(&server);
        exit(EPITECH_FAILURE);
    }
    for (size_t i = 0; i < MAP_HEIGHT; i += 1) {
        printf("%s\n", server->map[i]);
    }
    fclose(file);
}
