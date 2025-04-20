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

static void send_end_map(
    server_t *server, size_t player_index, size_t line_index)
{
    const char endl[] = "\r\n";
    const char end_map[] = "END_MAP\r\n";

    if (line_index == MAP_HEIGHT - 1) {
        if (send(server->players[player_index]->socket->fd, endl, strlen(endl),
                0) < 0) {
            fprintf(stderr, "Unable to send \"\\r\\n\" for map\n");
            server->destroy(&server);
            exit(EXIT_FAILURE);
        }
        debug(server, endl, TRUE);
        if (send(server->players[player_index]->socket->fd, end_map,
                strlen(end_map), 0) < 0) {
            fprintf(stderr, "Unable to send end_map\n");
            server->destroy(&server);
            exit(EXIT_FAILURE);
        }
        debug(server, end_map, TRUE);
    }
}

static void send_start_map(
    server_t *server, size_t player_index, size_t line_index)
{
    const char start_map[] = "START_MAP\r\n";

    if (line_index == 0) {
        send(server->players[player_index]->socket->fd, start_map,
            strlen(start_map), 0);
        debug(server, start_map, TRUE);
    }
}

static void send_map_line(server_t *server, size_t i)
{
    for (size_t j = 0; j < server->nb_player; j += 1) {
        send_start_map(server, j, i);
        if (send(server->players[j]->socket->fd, server->map[i],
                strlen(server->map[i]), 0) < 0) {
            fprintf(stderr, "Unable to send map\n");
            server->destroy(&server);
            exit(EXIT_FAILURE);
        }
        debug(server, server->map[i], TRUE);
        server->players[j]->map[i] = strdup(server->map[i]);
        if (send(server->players[j]->socket->fd, "\n", 1, 0) < 0) {
            fprintf(stderr, "Unable to send map\n");
            server->destroy(&server);
            exit(EXIT_FAILURE);
        }
        debug(server, "\n", TRUE);
        send_end_map(server, j, i);
    }
}

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
        send_map_line(server, i);
    }
}

static void check_line_length(server_t *server, char *buff, size_t nb_lines)
{
    if (strlen(buff) > MAP_LENGTH_MAX) {
        fprintf(stderr, "Map too long\n");
        server->destroy(&server);
        free(buff);
        exit(EXIT_FAILURE);
    }
    if (buff[strlen(buff) - 1] == '\n') {
        buff[strlen(buff) - 1] = '\0';
    }
    if (nb_lines > 0) {
        if (strlen(buff) != strlen(server->map[nb_lines - 1])) {
            fprintf(stderr, "Map with inconsistent length: %zu, %zu, %zu\n",
                nb_lines, strlen(buff), strlen(server->map[nb_lines - 1]));
            server->destroy(&server);
            exit(EXIT_FAILURE);
        }
    }
}

static void check_map_height(server_t *server, size_t nb_lines)
{
    if (nb_lines != MAP_HEIGHT) {
        fprintf(stderr, "Unable to open the map\n");
        server->destroy(&server);
        exit(EPITECH_FAILURE);
    }
}

static FILE *open_file(server_t *server)
{
    FILE *file = NULL;

    if (server == NULL || server->map_file == NULL) {
        fprintf(stderr, "Unable to access server map file");
        server->destroy(&server);
        exit(EPITECH_FAILURE);
    }
    file = fopen(server->map_file, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open the map\n");
        server->destroy(&server);
        exit(EPITECH_FAILURE);
    }
    return file;
}

static void check_end_map(server_t *server, size_t nb_lines)
{
    if (nb_lines == MAP_HEIGHT) {
        fprintf(stderr, "Map with incorrect height\n");
        server->destroy(&server);
        exit(EXIT_FAILURE);
    }
}

void load_map(server_t *server)
{
    char *buff = NULL;
    size_t size_read = 0;
    FILE *file = open_file(server);
    size_t nb_lines = 0;

    while (getline(&buff, &size_read, file) > 0) {
        check_line_length(server, buff, nb_lines);
        check_end_map(server, nb_lines);
        server->map[nb_lines] = strdup(buff);
        nb_lines += 1;
        if (buff != NULL) {
            free(buff);
            buff = NULL;
        }
    }
    if (buff != NULL)
        free(buff);
    check_map_height(server, nb_lines);
    fclose(file);
}
