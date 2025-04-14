/*
** EPITECH PROJECT, 2025
** Server run
** File description:
** Main loop of the server struct
*/

#include "cleanup.h"
#include "instructions.h"
#include "my_macros.h"
#include "server.h"
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>

static void store_player(server_t *server, struct pollfd *pfds)
{
    server->players[server->nb_player] = create_player(pfds);
    server->nb_player += 1;
    if (server->players[server->nb_player - 1] == NULL) {
        fprintf(stderr, "Unable to create player");
        free_server(&server);
        exit(EPITECH_FAILURE);
    }
}

static void accept_connection(server_t *server)
{
    struct pollfd *pfds = NULL;
    const char *msg = "220 Connection established.\r\n";

    pfds = malloc(sizeof(struct pollfd));
    if (!pfds) {
        fprintf(stderr, "Unable to alloc pollfd\n");
        free_server(&server);
        exit(EPITECH_FAILURE);
    }
    pfds->fd = accept(server->socket->fd, (struct sockaddr *)server->address,
        &server->socklen);
    if (pfds->fd < 0) {
        free(pfds);
        fprintf(stderr, "Unable to accept connection\n");
        return;
    }
    pfds->events = POLLIN;
    store_player(server, pfds);
    write(pfds->fd, msg, strlen(msg));
}

static int check_remove_socket(
    server_t *server, struct pollfd *pfds, const size_t i)
{
    if (pfds->revents & POLLHUP ||
        pfds->revents & POLLERR) {
        if (i == 0) {
            fprintf(stderr, "Error on server socker\n");
            server->is_running = FALSE;
            return TRUE;
        }
        free_player(&(server->players[i - 1]));
        server->nb_player -= 1;
        for (size_t j = i - 1; j < NB_PLAYER_MAX - 1; j += 1) {
            server->players[j] = server->players[j + 1];
        }
        server->players[NB_PLAYER_MAX - 1] = NULL;
        return TRUE;
    }
    return FALSE;
}

static void check_pfds(server_t *server, struct pollfd *players_pfds, size_t i)
{
    if (check_remove_socket(server, players_pfds, i))
        return;
    if (players_pfds[i].revents & POLLIN) {
        if (i == 0) {
            accept_connection(server);
            return;
        }
        execute_instructions(server, server->players[i]);
    }
}

static void loop_poll(
    struct pollfd *players_pfds, server_t *server, size_t nb_players)
{
    for (size_t i = 0; i < nb_players + 1; i += 1) {
        check_pfds(server, players_pfds, i);
    }
}

static struct pollfd *get_pfds_from_players(server_t *server)
{
    struct pollfd *pfds =
        malloc(sizeof(struct pollfd) * (server->nb_player + 1));

    if (!pfds) {
        fprintf(stderr, "Unable to alloc pfds");
        free_server(&server);
        exit(EPITECH_FAILURE);
    }
    pfds[0] = *server->socket;
    for (size_t i = 1; i < server->nb_player + 1; i += 1) {
        pfds[i] = *server->players[i - 1]->socket;
    }
    return pfds;
}

static void loop_server(server_t *server)
{
    int ret = 0;
    size_t nb_players = 0;
    struct pollfd *players_pfds = NULL;

    players_pfds = get_pfds_from_players(server);
    nb_players = server->nb_player;
    ret = poll(players_pfds, nb_players + 1, -1);
    if (ret > 0) {
        loop_poll(players_pfds, server, nb_players);
    }
    free(players_pfds);
}

int run_server(server_t *this)
{
    signal(SIGPIPE, SIG_IGN);
    while (this->is_running) {
        loop_server(this);
    }
    return SUCCESS;
}
