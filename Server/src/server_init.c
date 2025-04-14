/*
** EPITECH PROJECT, 2025
** Server init
** File description:
** Init the server
*/

#include "cleanup.h"
#include "my_macros.h"
#include "server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <map.h>

static void bind_server(server_t *server)
{
    if (bind(server->socket->fd, (struct sockaddr *)server->address,
            server->socklen) < 0) {
        server->destroy(&server);
        fprintf(stderr, "Unable to bind the socket\n");
        exit(EPITECH_FAILURE);
    }
}

static void listen_to_server(server_t *server)
{
    if (listen(server->socket->fd, NB_PLAYER_MAX) < 0) {
        server->destroy(&server);
        fprintf(stderr, "Unable to listen to socket\n");
        exit(EPITECH_FAILURE);
    }
    fprintf(stdout, "Server listening on port %d...\n", server->port);
}

static void init_socket(server_t *this)
{
    this->socket = malloc(sizeof(struct pollfd));
    if (!this->socket) {
        this->destroy(&this);
        fprintf(stderr, "Unable to alloc socket\n");
        exit(EPITECH_FAILURE);
    }
    this->socket->events = POLLIN;
    this->socket->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socket->fd < 0) {
        this->destroy(&this);
        fprintf(stderr, "Unable to init socket\n");
        exit(EPITECH_FAILURE);
    }
}

static void init_address(server_t *this, int portNumber)
{
    this->address = malloc(sizeof(struct sockaddr_in));
    if (!this->address) {
        this->destroy(&this);
        fprintf(stderr, "Unable to alloc sockadrr_in\n");
        exit(EPITECH_FAILURE);
    }
    this->address->sin_addr.s_addr = INADDR_ANY;
    this->address->sin_port = htons(portNumber);
    this->address->sin_family = AF_INET;
}

static void send_message(player_t *player, const char *msg)
{
    char endl[] = "\r\n";

    if (player == NULL || player->socket == NULL || player->socket->fd < 0) {
        return;
    }
    write(player->socket->fd, msg, strlen(msg));
    write(player->socket->fd, endl, strlen(endl));
}

static void init_server_methods(server_t *this)
{
    this->run = run_server;
    this->destroy = free_server;
    this->send = send_message;
    this->send_map = send_map;
}

static void init_server_attribut(
    server_t *this, int port, const char *map, int debug)
{
    this->is_running = TRUE;
    this->is_debug = debug;
    this->port = port;
    this->map_file = strdup(map);
    this->nb_player = 0;
}

server_t *create_server(int port, const char *map, int debug)
{
    server_t *server = malloc(sizeof(server_t));

    if (!server) {
        fprintf(stderr, "Alloc failed for server");
        return NULL;
    }
    if (!map) {
        fprintf(stderr, "Wrong map");
        return NULL;
    }
    init_server_methods(server);
    init_server_attribut(server, port, map, debug);
    init_address(server, port);
    server->socklen = sizeof(*server->address);
    init_socket(server);
    bind_server(server);
    for (size_t i = 0; i < NB_PLAYER_MAX; i += 1) {
        server->players[i] = NULL;
    }
    listen_to_server(server);
    return server;
}
